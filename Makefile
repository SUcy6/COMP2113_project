FLAGS = -pedantic-errors -std=c++11 -I ~/group90/include -I ~/group90/include/ncursestw -L ~/group90/lib -lncursestw -ldl -pthread -l ncurses -ObjC++

check_collision.o: check_collision.cpp tetris.h
	g++ $(FLAGS) -c $< 

combine_tetris.o: combine_tetris.cpp tetris.h
	g++ $(FLAGS) -c $< 

elimination.o: elimination.cpp tetris.h
	g++ $(FLAGS) -c $< 

playing_field.o: playing_field.cpp tetris.h
	g++ $(FLAGS) -c $<

tetris_piece.o: tetris_piece.cpp tetris.h
	g++ $(FLAGS) -c $<

falling_ctr.o: falling_ctr.cpp tetris.h
	g++ $(FLAGS) -c $<

update_record.o: update_record.cpp tetris.h
	g++ $(FLAGS) -c $<

main.o: main.cpp tetris.h
	g++ $(FLAGS) -c $<

main: main.o tetris_piece.o playing_field.o elimination.o combine_tetris.o check_collision.o falling_ctr.o update_record.o
	g++ $(FLAGS) $^ -o $@ 


clean:
	rm -f main main.o tetris_piece.o playing_field.o elimination.o combine_tetris.o check_collision.o falling_ctr.o update_record.o main.tgz
tar:
	tar -czvf main.tgz *.cpp *.h
.PHONY: clean tar  
