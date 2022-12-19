#include "Movie.h"

using namespace std;

void test();

int main()
{
	cout << "Start testing\n" << endl;
	test();
	cout << "\nFinished testing" << endl;
	return 0;
}

void test()
{
	cout <<"------------------Testing Movie class not empty constructor with setters and addActor----------------\n";
	Movie movie(152,2008,5,14.99,"The Dark Knight");
	movie.setMoviePrice(23.3);
	movie.setMovieTime(520);
	movie.setMovieYearOut(2022);
	movie.setNumberOfActors(6);
	movie.addActor("Kirito","ZPF",2002);
	movie.addActor("Christian","Bale",1974);
	movie.addActor("Heath","Ledger",1979);
	movie.addActor("Aaron","Eckhart",1968);
	movie.addActor("Michael","Caine",1933);
	movie.addActor("Maggie","Gyllenhaal",1977);
	cout << "Output the detail of the movie:" << endl;
	movie.printMovieInfo();

	cout << "-----------------Testing Movie class empty constructor with setters and addActor---------------------\n";
	Movie movie_temp;
	movie_temp.setMovieTime(152);
	movie_temp.setMovieYearOut(2008);
	movie_temp.setNumberOfActors(5);
	movie_temp.setMoviePrice(14.99);
	movie_temp.setMovieTitle("The Dark Knight");

	movie_temp.printMovieInfo();
	Actor actor("Bale","Christian",1974);
	Actor actor_temp;
	actor_temp.setBirthYear(1974);
	actor_temp.setFirstName("Christian");
	actor_temp.setLastName("Bale");
	
	movie_temp.addActor(actor);
	movie_temp.addActor("Christian", "Bale", 1974);
	movie_temp.addActor("Heath", "Ledger", 1979);
	movie_temp.addActor("Aaron", "Eckhart", 1968);
	movie_temp.addActor("Michael", "Caine", 1933);
	movie_temp.printMovieInfo();
		
	movie_temp.setNumberOfActors(2);
	movie_temp.printMovieInfo();

	Movie temp;
	temp = movie;
	cout <<endl<< "Test the copy constructor:"<<endl;
	
	cout<<"Before change:"<<endl;	
	cout << endl;
	movie.printMovieInfo();
	cout << endl;
	temp.printMovieInfo();

	temp.setMovieTitle("The Legend of 1900");
	temp.setMovieTime(124);
	temp.setMoviePrice(44);
	temp.setMovieYearOut(1998);
	temp.addActor(actor);
	cout << endl;
	cout << "After change:"<<endl;
	cout << endl;
	movie.printMovieInfo();
	cout << endl;
	temp.printMovieInfo();

	return ;
}