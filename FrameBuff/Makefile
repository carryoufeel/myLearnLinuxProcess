OBJ:=app
OBJS+=FrameBuff.c
OBJS+=Main.c 
OBJS+=Log.c 
OBJS+=font_8x16.c
OBJS+=ziku.c
OBJS+=Mouse.c
CC:=gcc

$(OBJ):$(OBJS)
	$(CC) $^ -o $@ -ljpeg -lpthread
.PHONY:
clean:
	rm $(OBJ)
