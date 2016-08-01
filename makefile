  
#VPATH=.:src  #make find file in this directory,use : depart,or use vpath 

vpath %.h   src/includes # .h at src/includes
vpath %.hpp src/includes # .hpp at src/includes
vpath %.c   src/src      # .c at src/src
vpath %.cpp src/src      # .cpp at src/src
  
APP = tst.bin

inc = -Isrc/includes # or use C_INCLUDE_PATH ,CPLUS_INCLUDE_PATH envir_path
inc += -Isrc/src	 # += 

targ := $(shell ls ./src/src)
objs_:= $(patsubst %.c,%.o,$(targ))
objs := $(patsubst %.cpp,%.o,$(objs_)) 

$(APP):$(objs)
	g++ -o $@ $(objs) -lm #maybe use gcc -Istdc++ 

%.o:%.c
	echo $(inc)
	gcc $(inc) -c $^

%.o:%.cpp
	g++ $(inc) -c $^


.PHONY:clean
clean:
	rm -f *.o $(APP) 
