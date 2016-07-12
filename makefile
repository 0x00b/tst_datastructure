  
#VPATH=.:src  #make find file in this directory,use : depart,or use vpath 

vpath %.h   src/includes # .h at src/includes
vpath %.hpp src/includes # .hpp at src/includes
vpath %.c   src/src      # .c at src/src
vpath %.cpp src/src      # .cpp at src/src
  
inc = -Isrc/includes # or use C_INCLUDE_PATH ,CPLUS_INCLUDE_PATH envir_path
inc += -Isrc/src	 # += 

objs = tst_avltree.o tst_tree.o tst_rbtree.o tst_main.o 

rbt:$(objs)
	g++ -o $@ $(objs) -lm #maybe use gcc -Istdc++ 

tst_tree.o:tst_tree.cpp tst_traits.hpp tst_construct.hpp tst_queue.hpp tst_stack.hpp tst_rbtree.h 
	gcc $(inc) -c $<
	
tst_main.o:tst_main.cpp tst_queue.hpp tst_stack.hpp tst_rbtree.h tst_tree.hpp 
	gcc $(inc) -c $<
	
tst_rbtree.o:tst_rbtree.c
	gcc $(inc) -c $^

tst_avltree.o:tst_avltree.c
	gcc $(inc) -c $^

.PHONY:clean
clean:
	rm -f *.o rbt 
