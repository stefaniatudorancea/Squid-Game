using namespace std;
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>

vector<vector<string>> participants_array;

class Participants
{
        private:
        string lastName;
        string firstName;
        string city;
        int debt;
        int weight;

    public:

        Participants()
        {
        }

        Participants(string ln, string fn, string c, int d, int w)
        {
            lastName = ln;
            firstName = fn;
            firstName = c;
            debt = d;
            weight = w;
        }

        void setLastName(string lastName) {this->lastName = lastName;}
        void setFirstName(string firstName) {this->firstName = firstName;}
        void setCity(string city) {this->city = city;}
        void setDebt(int debt) {this->debt = debt;}
        void setWeight(int weight) {this->weight = weight;}

        string getLastName() {return this->lastName;}
        string getFirstName() {return this->firstName;}
        string getCity() {return this->city;}
        int getDebt() {return this->debt;}
        int getWeight() {return this->weight;}

        ~Participants()
        {
        }
};

class Competitor : public Participants
{
    int contest_number;
    int sv;

    public:

    Competitor()
    {
    }

    Competitor(string ln, string fn, string c, int d, int w, int cn, int s): Participants(ln, fn, c, d, w)
    {
        contest_number = cn;
        sv = s;
    }

    void setContestNumber(int contest_number) {this->contest_number = contest_number;}
    int getContestNumber() {return this->contest_number;}

    void setSupervisor(int sv) {this->sv = sv;}
    int getSupervisor() {return this->sv;}

    ~Competitor()
    {

    }
};

class Supervisor : public Participants
{
    string shape_mask;

    public:

    Supervisor()
    {
    }

    Supervisor(string ln, string fn, string c, int d, int w, string sm): Participants(ln, fn, c, d, w)
    {
        shape_mask = sm;
    }

    void setShapeMask(string shape_mask) {this->shape_mask = shape_mask;}
    string getShapeMask() {return this->shape_mask;}

    ~Supervisor()
    {

    }
};

//that function reads from the csv file the list of names and cities and saves the information in participants_array
void read_participants()
{
    int r1, r2;
    string d, w;

    string fname = "participantss.csv";

	vector<string> row;
	string line, word;

	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while(getline(str, word, ','))
				row.push_back(word);

			r1 = rand() % 90000 + 10000;
            r2 = rand() % 50 + 50;

            d = to_string(r1);
            w = to_string(r2);

            row.push_back(d);
            row.push_back(w);

			participants_array.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
}

Supervisor list_of_supervisors[9];
Competitor list_of_competitors[99], competitors1[49];

//this function distributes the participants into the two categories (competitors and supervisors)
void partition(int id_supervisor[])
{
    int id, k = 0;
    //9 numbers are randomly generated to select supervisors
    while(k < 9)
    {
        int ok = 0;
        id = rand() % 108 + 1;
        for(int i = 0; i < k; i++)
            if(id == id_supervisor[i])
                ok = 1;
        if(ok == 0)
            id_supervisor[k++] = id;

    }

    cout<<"The distribution of supervisors and competitors has been carried out: \n\n";
    //the object vector of the supervisors is created
    for(int i = 0; i < 9; i++)
    {
        id = id_supervisor[i];
        list_of_supervisors[i].setLastName(participants_array[id-1][1]);
        list_of_supervisors[i].setFirstName(participants_array[id-1][2]);
        list_of_supervisors[i].setCity(participants_array[id-1][3]);

        int r1, r2;
        r1 = rand() % 90000 + 10000;
        r2 = rand() % 50 + 50;
        list_of_supervisors[i].setWeight(r2);
        list_of_supervisors[i].setDebt(r1);

        if(i < 3)
            list_of_supervisors[i].setShapeMask("rectangle");
        if(i >= 3 && i < 6)
            list_of_supervisors[i].setShapeMask("triangle");
        if(i >= 6)
            list_of_supervisors[i].setShapeMask("circle");
    }

    //the supervisors and information about them are displayed
    cout<<"The supervisors are: "<<endl;
    for(int i = 0; i < 9; i++)
    {
      cout<<i+1<<". "<<list_of_supervisors[i].getLastName()<<" "<<list_of_supervisors[i].getFirstName()<<" from "<<list_of_supervisors[i].getCity()
      <<" whith "<<list_of_supervisors[i].getWeight()<<" kg and a debt of "<<list_of_supervisors[i].getDebt()<<"$. His mask is in the shape of a "<<list_of_supervisors[i].getShapeMask()<<endl;
    }

    //the object vector of the competitors is created
    int ids[109] = {0};

    for(int i = 0; i < 9; i++)
    {
        k = id_supervisor[i];
        ids[k] = 1;
    }

    int n = 0, a = 0, b = 0;
    for(int i = 1; i <= 108; i++)
        if(ids[i] == 0)
        {
            list_of_competitors[n].setLastName(participants_array[i-1][1]);
            list_of_competitors[n].setFirstName(participants_array[i-1][2]);
            list_of_competitors[n].setCity(participants_array[i-1][3]);

            int r1, r2;
            r1 = rand() % 90000 + 10000;
            r2 = rand() % 50 + 50;
            list_of_competitors[n].setDebt(r1);
            list_of_competitors[n].setWeight(r2);
            list_of_competitors[n].setContestNumber(n+1);

            //this if allocates a supervisor to the competitor
            if(a <= 10)
            {
                list_of_competitors[n].setSupervisor(id_supervisor[b]);
                a++;
            }
            else
            {
                b++;
                a = 1;
                list_of_competitors[n].setSupervisor(id_supervisor[b]);
            }
            n++;
        }

    //the competitors and information about them are displayed
    cout<<"\nThe competitors are: "<<endl;
    for(int i = 0; i < 99; i++)
    {
      cout<<list_of_competitors[i].getContestNumber()<<". "<<list_of_competitors[i].getLastName()<<" "<<list_of_competitors[i].getFirstName()<<" from "<<list_of_competitors[i].getCity()<<" whith ";
      cout<<list_of_competitors[i].getWeight()<<" kg and a debt of "<<list_of_competitors[i].getDebt()<<"$. ";

      int x = list_of_competitors[i].getSupervisor();
      for(int j = 0; j < 9; j++)
        if(x == id_supervisor[j])
            cout<<"His supervisor is "<<list_of_supervisors[j].getLastName()<<" "<<list_of_supervisors[j].getFirstName()<<endl;
    }

}

void red_light_green_light()
{
    int i, d, w;
    string ln, fn, c, sm;

    cout<<"\n\nSTART Red Light, Green Light";
    cout<<"\nAs a result of this game, the following competitors remained: \n\n";
    for(int i = 0; i < 50; i++)
    {
        competitors1[i].setFirstName(list_of_competitors[i*2].getFirstName());
        competitors1[i].setLastName(list_of_competitors[i*2].getLastName());
        competitors1[i].setCity(list_of_competitors[i*2].getCity());
        competitors1[i].setDebt(list_of_competitors[i*2].getDebt());
        competitors1[i].setWeight(list_of_competitors[i*2].getWeight());
        competitors1[i].setContestNumber(list_of_competitors[i*2].getContestNumber());
        competitors1[i].setSupervisor(list_of_competitors[i*2].getSupervisor());

      cout<<competitors1[i].getContestNumber()<<". "<<competitors1[i].getLastName()<<" "<<competitors1[i].getFirstName()<<endl;
    }
}

void tug_of_war(Competitor competitors2[])
{
    cout<<"\n\nSTART Tug of War";
    cout<<"\nAs a result of this game, the following competitors remained: \n\n";
   int teamA[12], teamB[12], teamC[12], teamD[12];
   int r, v[50], i, j, ok, k = 1, w[50];

   //competitors are randomly assigned to teams
   i = 0;
   j = 0;
   while(i < 50)
   {
       r = rand() % 50 + 1;
       ok = 1;
       for(k = 0; k <= i; k++)
            if(r == v[k])
                ok = 0;
        if(ok == 1)
        {
            v[j] = r;
            i++;
            w[j++] = competitors1[r-1].getContestNumber();
        }
   }

    k = 0;
    for(i = 0; i < 12; i++)
    {
        teamA[i] = w[k++];
        teamB[i] = w[k++];
        teamC[i] = w[k++];
        teamD[i] = w[k++];
    }

    //calculate the weight for each team

    int wA, wB, wC, wD;
    wA = wB = wC = wD = 0;

    for(i = 0; i < 12; i++)
    {
        wA += competitors1[teamA[i]/2].getWeight();
        wB += competitors1[teamB[i]/2].getWeight();
        wC += competitors1[teamC[i]/2].getWeight();
        wD += competitors1[teamD[i]/2].getWeight();
    }

    int x = max(max(wA, wB), max(wC, wD));

    //the competitors2 object is created, where are the competitors who will go to the next stage

    //initially, we add the two competitors who were not assigned to teams
    for(int i = 0; i < 2; i++)
    {
        competitors2[i].setFirstName(competitors1[w[48+i]/2].getFirstName());
        competitors2[i].setLastName(competitors1[w[48+i]/2].getLastName());
        competitors2[i].setCity(competitors1[w[48+i]/2].getCity());
        competitors2[i].setDebt(competitors1[w[48+i]/2].getDebt());
        competitors2[i].setWeight(competitors1[w[48+i]/2].getWeight());
        competitors2[i].setContestNumber(competitors1[w[48+i]/2].getContestNumber());
        competitors2[i].setSupervisor(competitors1[w[48+i]/2].getSupervisor());
    }

    //we create the team vector that contains the contest number for the participants of the winning team
    int team[12];
    if(wA == x)
        for(i = 0; i < 12; i++)
                team[i] = teamA[i];
    if(wB == x)
        for(i = 0; i < 12; i++)
                team[i] = teamB[i];
    if(wC == x)
        for(i = 0; i < 12; i++)
                team[i] = teamC[i];
    if(wD == x)
        for(i = 0; i < 12; i++)
                team[i] = teamD[i];

    //add the competitors from the winning team to the competitors2 object
    for(int i = 2; i < 14; i++)
    {
        competitors2[i].setFirstName(competitors1[team[i-2]/2].getFirstName());
        competitors2[i].setLastName(competitors1[team[i-2]/2].getLastName());
        competitors2[i].setCity(competitors1[team[i-2]/2].getCity());
        competitors2[i].setDebt(competitors1[team[i-2]/2].getDebt());
        competitors2[i].setWeight(competitors1[team[i-2]/2].getWeight());
        competitors2[i].setContestNumber(competitors1[team[i-2]/2].getContestNumber());
        competitors2[i].setSupervisor(competitors1[team[i-2]/2].getSupervisor());
    }

    for(i = 0; i < 14; i++)
        cout<<competitors2[i].getContestNumber()<<". "<<competitors2[i].getLastName()<<" "<<competitors2[i].getFirstName()<<endl;
}

void marbles(Competitor competitors3[], Competitor competitors2[])
{
    cout<<"\n\nSTART Marbles";
    cout<<"\nAs a result of this game, the following competitors remained: \n\n";

    int i, r, j = 0;
    for(i = 0; i < 14; i = i + 2)
    {
        r = rand() % 2;

        competitors3[j].setFirstName(competitors2[i + r].getFirstName());
        competitors3[j].setLastName(competitors2[i + r].getLastName());
        competitors3[j].setCity(competitors2[i + r].getCity());
        competitors3[j].setDebt(competitors2[i + r].getDebt());
        competitors3[j].setWeight(competitors2[i + r].getWeight());
        competitors3[j].setContestNumber(competitors2[i + r].getContestNumber());
        competitors3[j].setSupervisor(competitors2[i + r].getSupervisor());
        j++;
    }

    for(i = 0; i < 7; i++)
        cout<<competitors3[i].getContestNumber()<<". "<<competitors3[i].getLastName()<<" "<<competitors3[i].getFirstName()<<endl;
}

//this function returns the winner to play rock-paper-scissors
int rps(int a, int b)
{
    if(a == b)
        return 3;

    if(a == 1)
        if(b == 2)
            return 0;
        else
            return 1;

    if(a == 2)
        if(b == 1)
            return 1;
        else
            return 0;

    if(a == 3)
        if(b == 1)
            return 1;
        else
            return 0;
}

void genken(Competitor competitors3[], int *winner_number)
{
    cout<<"\n\nSTART Genken\n";


    int i, j, competitors_genken[2], competitors[7], aux, r0, r1;

    for(i = 0; i < 7; i++)
        competitors[i] = competitors3[i].getContestNumber();

    for (i = 0; i < 7; i++)
        for (j = 0; j < 7-i ; j++)
            if (competitors[j] < competitors[j+1])
                {
                    aux = competitors[j];
                    competitors[j] = competitors[j+1];
                    competitors[j+1] = aux;
                }

     for(i = 0; i < 7; i++)

     competitors_genken[0] = competitors[0];
     competitors_genken[1] = competitors[1];

     i = 2;
     while(i < 8)
     {
         r0 = rand() % 3 + 1;
         r1 = rand() % 3 + 1;

         if(rps(r0, r1) == 0)
         {
            competitors_genken[1] = competitors[i++];
         }


         if(rps(r0, r1) == 1)
         {
             competitors_genken[0] = competitors[i++];
         }
     }

     int x;
     if(rps(r0, r1) == 0)
        cout<<endl<<"The winner of the game is "<<list_of_competitors[competitors_genken[0]-1].getLastName()<<" "<<list_of_competitors[competitors_genken[0]-1].getFirstName()<<endl, *winner_number = competitors_genken[0];
     else
        cout<<endl<<"The winner of the game is "<<list_of_competitors[competitors_genken[1]-1].getLastName()<<" "<<list_of_competitors[competitors_genken[1]-1].getFirstName()<<endl, *winner_number = competitors_genken[1];
}

void calculate_amount_win(int winner_number)
{
    int amount_win = 0;
    for(int i = 0; i < 99; i++)
        amount_win += list_of_competitors[i].getDebt();

    amount_win = amount_win - list_of_competitors[winner_number - 1].getDebt();

    cout<<list_of_competitors[winner_number - 1].getLastName()<<" "<<list_of_competitors[winner_number - 1].getFirstName()<<" earned "<<amount_win<<"$.\n\n";
}

void calculate_amounts_supervisors(int winner_number, int id_supervisor[], int amounts_supervisors[][2])
{
    int k=0, amount, i, j, aux;


    for(i = 0; i < 9; i++)
    {
        if(id_supervisor[i] == list_of_competitors[winner_number - 1].getSupervisor())
        {
            cout<<"The supervisor of the winner, "<<list_of_supervisors[i].getLastName()<<" "<<list_of_supervisors[i].getFirstName()<<" received "<<10 * list_of_competitors[winner_number - 1].getDebt()<<"$. \n";
            amounts_supervisors[i][0] = i;
            amounts_supervisors[i][1] = 10 * list_of_competitors[winner_number - 1].getDebt();
        }
        else
        {
            amount = 0;
            for(int j = 0; j < 99; j++)
                if(list_of_competitors[j].getSupervisor() == id_supervisor[i])
                    amount += list_of_competitors[j].getDebt();

            amount -= list_of_supervisors[i].getDebt();
            amounts_supervisors[i][0] = i;
            amounts_supervisors[i][1] = amount;
        }
    }


    for (i = 0; i < 9; i++)
        for (j = 0; j < 9-i ; j++)
            if (amounts_supervisors[j][1] < amounts_supervisors[j+1][1])
                {
                    aux = amounts_supervisors[j][1];
                    amounts_supervisors[j][1] = amounts_supervisors[j+1][1];
                    amounts_supervisors[j+1][1] = aux;

                    aux = amounts_supervisors[j][0];
                    amounts_supervisors[j][0] = amounts_supervisors[j+1][0];
                    amounts_supervisors[j+1][0] = aux;
                }

    for(int i = 1; i < 9; i++)
       cout<<list_of_supervisors[amounts_supervisors[i][0]].getLastName()<<" "<<list_of_supervisors[amounts_supervisors[i][0]].getFirstName()<<" received "<<amounts_supervisors[i][1]<<"$."<<endl;

}


void winning_team(int amounts_supervisors[][2])
{
    int circle_team = 0, rectangle_team = 0, triangle_team = 0, i, highest_amount;

    for(i = 0; i < 9; i++)
    {
        if(list_of_supervisors[amounts_supervisors[i][0]].getShapeMask() == "triangle")
            triangle_team += amounts_supervisors[i][1];
        if(list_of_supervisors[amounts_supervisors[i][0]].getShapeMask() == "circle")
            circle_team += amounts_supervisors[i][1];
        if(list_of_supervisors[amounts_supervisors[i][0]].getShapeMask() == "rectangle")
            rectangle_team += amounts_supervisors[i][1];
    }

    highest_amount = max(triangle_team, max(circle_team, rectangle_team));

    if(highest_amount == circle_team)
        cout<<"\nThe team that won the highest amount is the circle mask team: "<<circle_team<<"$. \n";
    if(highest_amount == triangle_team)
        cout<<"\nThe team that won the highest amount is the triangle mask team: "<<triangle_team<<"$. \n";
    if(highest_amount == rectangle_team)
        cout<<"\nThe team that won the highest amount is the rectangle mask team: "<<rectangle_team<<"$. \n";
}

int main()
{
   read_participants();
   int id_supervisor[9], amounts_supervisors[9][2];
   partition(id_supervisor);

   red_light_green_light();

    Competitor competitors2[14], competitors3[7], winner;
    tug_of_war(competitors2);
    marbles(competitors3, competitors2);

    int winner_number;
    genken(competitors3, &winner_number);
    calculate_amount_win(winner_number);
    calculate_amounts_supervisors(winner_number, id_supervisor, amounts_supervisors);
    winning_team(amounts_supervisors);

    participants_array.clear();

}
