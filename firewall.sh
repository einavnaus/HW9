#!/bin/bash
cat /dev/stdin > total_packets.txt
if [ -s total_packets.txt ]; then
	while read -r line ; do
		cat total_packets.txt > current_packets.txt
		line=$(echo "$line" | sed -e 's/ //' | sed -e 's/#.*//')
		if [[ "$line" == "" ]]; then
			continue
		fi
		IFS=',' read -r -a rules <<< "$line"
		for rule in "${rules[@]}" ; do
			if [[ "$rule" == "" ]]; then
				continue
			fi
			cat current_packets.txt | ./firewall.exe "$rule" > match_to_rule.txt 
			cat match_to_rule.txt > current_packets.txt
		done
		cat current_packets.txt >> matched_pckts.txt

	done <$1
	echo -e "$(<matched_pckts.txt)" | sed '/^$/d' | tr -d ' ' | sort | uniq 
	rm matched_pckts.txt match_to_rule.txt current_packets.txt total_packets.txt 
else
	rm total_packets.txt 
fi