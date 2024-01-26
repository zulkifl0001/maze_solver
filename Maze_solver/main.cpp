#include <iostream>
#include <fstream>

using namespace std;
class Maze{
private:
    int Nrow; //total rows
    int Ncol; //total columns
    char Nstate[20][20];//max usable maze size 20
    char Cdir; //currect direction
    int Crow; //current row
    int Ccol; //currect column
    int Trow;
    int Tcol;
public:
    Maze();
    Maze(const Maze &cpy);

    bool can_move_left();
    bool can_move_right();
    bool can_move_forward();
    bool can_move_back();

    void move_left();
    void move_right();
    void move_forward();
    void move_back();

    bool is_solved();
    char print_state();

};

template<class T>
class StackQueue{
private:

    int m;
    T *stackqueue;
public:
    StackQueue();
    void push_front(T n);
    void push_rear(T n);
    T pop_front();
    T pop_rear();
    T peek_front();
    void incfront();
    void incback();
    void print_elements();

    ~StackQueue(){
        delete[] stackqueue;
    }
};

Maze::Maze() {
    //code given in the question

    ifstream input_file; /* input file stream */
    input_file.open ("input_maze.txt");
    int nrow, ncol; /* number of rows and columns */
    input_file >> nrow >> ncol; /* read the size from file */
    Nrow=nrow;
    Ncol=ncol;
    char state[nrow][ncol];
    for(int i=0; i<nrow; ++i){
        for(int j=0; j<ncol; ++j){
            input_file >> state[i][j];
            Nstate[i][j]=state[i][j];
            //checking to see where our player starts from
            if(state[i][j]!='#' and state[i][j]!= '.' and state[i][j]!='T'){
                Crow=i;
                Ccol=j;
                Cdir=state[i][j];
            }
            //saving the location of the goal
            if(state[i][j]=='T'){
                Trow=i;
                Tcol=j;
            }
        }
    }
    input_file.close();
}
Maze::Maze(const Maze &cpy) {
    //copy vals
    Crow=cpy.Crow;
    Ccol=cpy.Ccol;
    Cdir=cpy.Cdir;

    for (int a=0;a<Nrow;a++){
        for(int b=0;b<Ncol;a++){
            Nstate[a][b]=cpy.Nstate[a][b];//copy all things in Nstate to the new Nstate
        }
    }

}

bool Maze::is_solved()  {
    //checks to see if T is still at its old location; if not then it has been solved;
    bool x=true;
    for(int i=0;i<Nrow;i++){
        for(int j=0;j<Ncol;j++){
            if(Nstate[i][j]=='T'){
                x=false;
            }
        }
    }
    return x;
}

//can move methods
//apply cases to see if there is a wall in the direction our robot wants to move
//if not then it can move in that direction
bool Maze::can_move_forward() {

    switch(Cdir){
        case 'E':
            if(Nstate[Crow][Ccol+1]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'S':
            if(Nstate[Crow+1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'N':
            if(Nstate[Crow-1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'W':
            if(Nstate[Crow][Ccol-1]!='#'){
                return true;
            }
            else{
                return false;
            }
    }

}
bool Maze::can_move_back() {
    switch(Cdir){
        case 'E':
            if(Nstate[Crow][Ccol-1]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'S':
            if(Nstate[Crow-1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'N':
            if(Nstate[Crow+1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'W':
            if(Nstate[Crow][Ccol+1]!='#'){
                return true;
            }
            else{
                return false;
            }
    }
}
bool Maze::can_move_right() {
    switch(Cdir){
        case 'E':
            if(Nstate[Crow+1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'S':
            if(Nstate[Crow][Ccol-1]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'N':
            if(Nstate[Crow][Ccol+1]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'W':
            if(Nstate[Crow-1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }
    }

}
bool Maze::can_move_left() {
    switch(Cdir){
        case 'E':
            if(Nstate[Crow-1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'S':
            if(Nstate[Crow][Ccol+1]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'N':
            if(Nstate[Crow][Ccol-1]!='#'){
                return true;
            }
            else{
                return false;
            }

        case 'W':
            if(Nstate[Crow+1][Ccol]!='#'){
                return true;
            }
            else{
                return false;
            }
    }

}

//actually moving methods
// call the respective can move functions and if they return true then move in the specified direction
//cases for the new direction
void Maze::move_forward() {
    if (this->can_move_forward()){
        switch(Cdir){
            case 'E':
                Nstate[Crow][Ccol]='.'; //change the old location to  .
                Ccol=Ccol+1;
                Nstate[Crow][Ccol]='E'; //put the robot at its new location
                break;
            case 'S':
                Nstate[Crow][Ccol]='.';
                Crow=Crow+1;
                Nstate[Crow][Ccol]='S';
                break;
            case 'N':
                Nstate[Crow][Ccol]='.';
                Crow=Crow-1;
                Nstate[Crow][Ccol]='N';
                break;

            case 'W':
                Nstate[Crow][Ccol]='.';
                Ccol=Ccol-1;
                Nstate[Crow][Ccol]='W';
                break;

        }
    }
    else{
        cout<<"cannot move forward"<<endl;
    }
}
void Maze::move_back() {
    if(this->can_move_back()){
        switch(Cdir){
            //reverse the directions before changing the position
            case 'E':
                Nstate[Crow][Ccol]='.';
                Ccol=Ccol-1;
                Cdir='W';
                Nstate[Crow][Ccol]=Cdir;

                break;
            case 'S':
                Nstate[Crow][Ccol]='.';
                Crow=Crow-1;
                Cdir='N';

                Nstate[Crow][Ccol]=Cdir;
                break;
            case 'N':
                Nstate[Crow][Ccol]='.';
                Crow=Crow+1;
                Cdir='S';
                Nstate[Crow][Ccol]=Cdir;
                break;


            case 'W':
                Nstate[Crow][Ccol]='.';
                Ccol=Ccol+1;
                Cdir='E';
                Nstate[Crow][Ccol]=Cdir;
                break;
        }
    }
    else{
        cout<<"cannot move back"<<endl;
    }
}
void Maze::move_right() {
    if (this->can_move_right()) {
        switch (Cdir) {
            //rotate the directions clockwise
            case 'E':
                Nstate[Crow][Ccol]='.';
                Crow = Crow + 1;
                Cdir = 'S';
                Nstate[Crow][Ccol]=Cdir;
                break;
            case 'S':
                Nstate[Crow][Ccol]='.';
                Ccol--;
                Cdir = 'W';
                Nstate[Crow][Ccol]=Cdir;
                break;

            case 'N':
                Nstate[Crow][Ccol]='.';
                Ccol++;
                Cdir = 'E';
                Nstate[Crow][Ccol]=Cdir;
                break;

            case 'W':
                Nstate[Crow][Ccol]='.';
                Crow--;
                Cdir = 'N';
                Nstate[Crow][Ccol]=Cdir;
                break;
        }
    }
    else{
        cout<<"cannot move right"<<endl;
    }
}
void Maze::move_left() {
    if(can_move_left()){
        switch(Cdir){
            //rotate the directions anti-clockwise
            case 'E':
                Nstate[Crow][Ccol]='.';
                Crow--;
                Cdir='N';
                Nstate[Crow][Ccol]=Cdir;
                break;

            case 'S':
                Nstate[Crow][Ccol]='.';
                Ccol++;
                Cdir='E';
                Nstate[Crow][Ccol]=Cdir;
                break;

            case 'N':
                Nstate[Crow][Ccol]='.';
                Ccol--;
                Cdir='W';
                Nstate[Crow][Ccol]=Cdir;
                break;

            case 'W':
                Nstate[Crow][Ccol]='.';
                Crow++;
                Cdir='S';
                Nstate[Crow][Ccol]=Cdir;
                break;
        }

    }
    else{
        cout<<"cannot move left";
    }
}

//cycle through the 2d array and print values at all locations
char Maze::print_state() {
    for(int i=0;i<Nrow;i++){
        for(int j=0;j<Ncol;j++){
            cout<<Nstate[i][j];
        }
        cout<<endl;
    }
}

template<class T>
//constructor for StackQueue
StackQueue<T>::StackQueue(){

    m=0;
    T *stackqueue = new T[m];
}

//push helper functions
//these functions create a new array with size 1 more than the old array and transfer all the elements of the previous list to the new one with the new array having one empty space
template<class T> void StackQueue<T>::incfront() {
    T *temp = new T[m+1];

    for (int i=0;i<m;i++){
        temp[i]=stackqueue[i];
    }

    delete[] stackqueue;//delete old stack queue

    stackqueue=temp;//new stack queue
    m=m+1;


}
//inc back leaves the first entry of the array blank and copies all the other elements to the incremented array
template<class T> void StackQueue<T>::incback() {
    T *temp = new T[m+1];

    for (int i=0;i<m;i++){
        temp[i+1]=stackqueue[i];
    }

    delete[] stackqueue;

    stackqueue=temp;
    m=m+1;
}

//push functions
//add new element to the rear or front
template<class T> void StackQueue<T>::push_front(T n) {
    incfront();//calls the helper function to create a bigger array
    stackqueue[m-1]=n; //push the val
}
template <class T>void StackQueue<T>::push_rear(T n) {
    incback();//incremenet the size of the array
    stackqueue[0]=n;//add to back of the array
}

//pop functions
//deletes and returns the first or last element
template<class T> T StackQueue<T>::pop_front() {
    //create a new array that has size that is 1 less than our original
    T *temp = new T[m-1];
    T out=stackqueue[m-1];
    for (int i=0;i<m;i++){
        temp[i]=stackqueue[i];
    }
    //delete the original
    delete[] stackqueue;
    //reassign our elements to our incremeneted array.
    stackqueue=temp;
    m=m-1;
    return out;

}
template<class T>T StackQueue<T>::pop_rear() {
    //decrements array
    T *temp = new T[m-1];
    T out=stackqueue[0];
    for (int i=1;i<m;i++){
        temp[i-1]=stackqueue[i];
    }
    //delete old
    delete[] stackqueue;
    //reassign
    stackqueue=temp;
    m=m-1;
    return out;
}

template<class T>T StackQueue<T>::peek_front() {
    if (m>0){
        return stackqueue[m-1];
    }
    //returns the first element of the stackqueue
}
//print all elements using a loop
template<class T> void StackQueue<T>::print_elements() {
    for (int i=0;i<m;i++){
        cout<<stackqueue[i];
    }

}


//solver function
void solver(){
    //create a stackqueue element
    StackQueue<char> stack;

    Maze maze=Maze();
    cout<<"first pass"<<endl;
    //loop while maze is not solved
    while(!maze.is_solved()){
        cout<<"SQ: ";
        stack.print_elements();
        cout<<endl;
        maze.print_state();
        cout<<endl;
        //applying the steps given in the question
        if(maze.can_move_left()){

            maze.move_left();
            if(stack.peek_front()!='B'){

                stack.push_front('L');
            }else{

                stack.pop_front();
                switch(stack.peek_front()){
                    case 'L':
                        stack.pop_front();
                        stack.push_front('F');
                        break;
                    case 'F':
                        stack.pop_front();
                        stack.push_front('R');
                        break;
                    case 'R':
                        stack.pop_front();
                        stack.push_front('B');
                }

            }

        }
        else if(maze.can_move_forward()){

            maze.move_forward();
            if(stack.peek_front()!='B'){
                stack.push_front('F');
            }else{
                stack.pop_front();
                switch(stack.peek_front()){
                    case 'L':
                        stack.pop_front();
                        stack.push_front('R');
                        break;
                    case 'F':
                        stack.pop_front();
                        stack.push_front('B');
                        break;
                }
            }
        }else if(maze.can_move_right()){
            maze.move_right();
            if(stack.peek_front()!='B'){
                stack.push_front('R');
            }else{
                stack.pop_front();
                if(stack.peek_front()=='R'){
                    stack.push_front('B');
                }
            }
        }else{
            maze.move_back();
            stack.push_front('B');
        }

    }
    cout<<"SQ: ";
    stack.print_elements();
    cout<<endl;
    maze.print_state();
    cout<<endl;
    cout<<"maze is solved"<<endl;

    Maze maze2= Maze();
    cout<<"second pass:"<<endl;
    cout<<"SQ: ";
    stack.print_elements();
    cout<<endl;
    maze2.print_state();

    //second pass
    //we use the steps detailed in the question
    while (!maze2.is_solved()){
        switch(stack.pop_rear()){
            case 'F':
                maze2.move_forward();
                break;
            case 'B':
                maze2.move_back();
                break;
            case 'R':
                maze2.move_right();
                break;
            case 'L':
                maze2.move_left();
                break;
        }
        cout<<"SQ: ";
        stack.print_elements();
        cout<<endl;
        maze2.print_state();
        cout<<endl;
    }
    cout<<"maze is solved";
}


int main() {
    solver();

}
