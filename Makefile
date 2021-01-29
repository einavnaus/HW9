CPP = g++
CPPFLAGS = -Wall -Wextra -L. -g -std=c++11
LIB_FLAGS = -fPIC -shared 
LIB_INPUT = input
LIB_SRCS = string.cpp field.cpp ip.cpp port.cpp
LIB = firewall
EXEC= firewall.exe
MAIN = main.cpp
RM = rm -f


all:${EXEC}

$(LIB):
	$(CPP) ${CPPFLAGS} ${LIB_FLAGS} ${LIB_SRCS} -o lib${LIB}.so


${EXEC}: ${LIB} 
	$(CPP) ${CPPFLAGS} ${MAIN} -o ${EXEC} -l$(LIB) -l$(LIB_INPUT)


clean:
	${RM} ${LIB} ${EXEC}
