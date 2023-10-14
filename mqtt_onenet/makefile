DST=all
SRC=main.c
CC=gcc 
FLAG=-g -lpaho-mqtt3cs -lrt 
LIBS+=/home/linux/code_test/mqtt_src/paho.mqtt.c-master/build/output
INC+=/usr/local/include

$(DST):$(SRC)
	$(CC) $(SRC) $(FLAG)
arm:$(SRC)
	arm-linux-gcc $(SRC) $(FLAG) -L $(LIBS) -I $(INC) 
clean:
	rm $(DST)
