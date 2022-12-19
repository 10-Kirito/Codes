#include "Movie.h"

using namespace std;

Movie::Movie()
{
    actors = NULL;
    actorArrayIndex = 0;

}

Movie::Movie(int time,int Year,int number,double price,std::string title)
{
    movieTime = time;
    movieYearOut = Year;
    numberOfActors = number;
    actorArrayIndex = 0;
    moviePrice = price;
    movieTitle = title;
    actors = new Actor[number];
}

Movie::~Movie()
{
    if (actors != NULL)
    {
        delete[] actors;
        actors = NULL;
    }
}

void Movie::setMovieTime(int time)
{
    movieTime = time;
}

int Movie::getMovieTime()
{
    return movieTime;
}

void Movie::setMovieYearOut(int year)
{
    movieYearOut = year;
}

int Movie::getMovieYearOut()
{
    return movieYearOut;
}

void Movie::setNumberOfActors(int num)
{
    if(actors == NULL){//if the cast is empty
        numberOfActors = num;
        actors = new Actor[numberOfActors];
    }else{
        if(num == 0){//if delete the cast
            delete []actors;
            actors = NULL;
            numberOfActors = num;
            actorArrayIndex = 0;
        }else if(num != numberOfActors){//if change the cast
            //if (actors != NULL) {
            Actor* temp;
            temp = new Actor[num];
            memcpy(temp, actors, min(num, actorArrayIndex) * sizeof(Actor));
            delete[] actors;
            actors = temp;
            actorArrayIndex = num <= numberOfActors ? num : (actorArrayIndex);
            numberOfActors = num;
            //}
            /*else {
                delete[] actors;
                actors = new Actor[num];
                numberOfActors = num;
            }*/
        }else
            return ;
    }
}

int Movie::getNumberOfActors()
{
    return numberOfActors;
}

void Movie::addActor(std::string first,std::string last,int birth)
{
    if(actors == NULL)
        return ;
    else if(actorArrayIndex <= (numberOfActors - 1)){
        Actor temp(first,last,birth);
        actors[actorArrayIndex] = temp;
        actorArrayIndex++;
    }else//the cast is full
        return ;
}

void Movie::addActor(Actor actor)
{
    if (actors == NULL)
        return;
    else if (actorArrayIndex <= (numberOfActors - 1)) {
        actors[actorArrayIndex] = actor;
        actorArrayIndex++;
    }
    else//the cast is full
        return;
}

void Movie::setMoviePrice(double price)
{
    moviePrice = price;
}

double Movie::getMoviePrice()
{
    return moviePrice;
}

void Movie::setMovieTitle(std::string title)
{
    movieTitle = title;
}

std::string Movie::getMovieTitle()
{
    return movieTitle;
}

void Movie::printMovieInfo()
{
    cout << "Title: "<<movieTitle<<", Published in: "<<movieYearOut<<endl;
    cout <<"Duration of Movie: "<<movieTime<<"minutes"<<endl;
    cout <<"Price: $"<<moviePrice<<endl;
    cout << "Actors:"<<endl;
    if(actorArrayIndex > 0){
        for(int i = 0;i < actorArrayIndex;i++)
            cout << actors[i]<<endl;
    }   
    return ;
}

Movie::Movie(const Movie & movie)
{
    *this = movie;
}

Movie & Movie::operator=(const Movie & movie)
{
    if(&movie != this)
    {    
        movieTime = movie.movieTime;
        movieYearOut = movie.movieYearOut;
        numberOfActors = movie.numberOfActors;
        actorArrayIndex = movie.actorArrayIndex;
        moviePrice = movie.moviePrice;
        movieTitle = movie.movieTitle;
        if(actors)
            delete [] actors;
        actors = new Actor[numberOfActors];
        for(int i = 0;i < actorArrayIndex;i++)
            actors[i] = movie.actors[i];
    }

    return *this;
}