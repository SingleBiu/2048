


TARGET:= game_2048
CC := arm-linux-gcc

# CSRCS保存的是工程中所有的.c的文件名列表
CSRCS :=$(wildcard *.c)


# OBJS保存的是工程中所有需要用到的.o的文件名列表
OBJS := $(patsubst %.c, %.o, $(CSRCS))


#INC保存的是工程中所有头文件的搜索路径
INC := -I ./  -I ./inc 

#LIBS保存的是工程所有需要用到的库以及库的搜索路径
LIBS := -L .

$(TARGET): $(OBJS)
	$(CC) $^ $(LIBS)  -o $@

%.o:%.c 
	$(CC) -c $< $(INC) -o $@
	
clean:
	rm -rf  $(OBJS)
	rm -rf $(TARGET)


	
