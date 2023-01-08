//Pedro Rodrigues 99300
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#define not_ancestor  0
#define ancestor_of_1 1
#define ancestor_of_2 2
#define ancestor_of_both 3
#define lowest_a_b 4
#define correct 1
#define wrong 0

using namespace std;


//Constants - Color_Cyclic
//Branco   -> 0
//Cinzento -> 1
//Verde    -> 2
//Vermelho -> 3
//Preto    -> 4

//Structs
struct Vertex
{
    int number;
    int color;
    int color_cyclic;
    vector<Vertex*> adjacents;
};

vector<Vertex*> all_Vertex;

//auxDFS
bool auxDFS(Vertex* vertex)
{
    vertex->color_cyclic = 1;
    int size = vertex->adjacents.size();
        
    for(int i = 0; i < size; i++)
    {
        Vertex* vertex2 = vertex->adjacents[i];
        if (vertex2->color_cyclic == 1)
            return true;

        if (vertex2->color_cyclic == 0 && auxDFS(vertex2))
            return true;
    }

    vertex->color_cyclic = 2;

    return false;
}

//isCyclic
bool isCyclic()
{
    int size = all_Vertex.size();

    for (int i = 0; i < size; i++)
    {
        Vertex* vertex = all_Vertex[i];
        vertex->color_cyclic = 0;
    }

    for (int i = 0; i < size; i++)
    {
        Vertex* vertex = all_Vertex[i];
        if (vertex->color_cyclic == 0)
        {
            if (auxDFS(vertex))
            {
                return true;
            }
        }
    }
    
    return false;
}

//doDFS
void doDFS(Vertex* vertex)
{
    int size = vertex->adjacents.size();
    vertex->color = ancestor_of_1;
    for (int i = 0; i < size; i++)
    {
        Vertex* vertex2 = vertex->adjacents[i];
        if (vertex2->color == not_ancestor)
        {
            vertex2->color = ancestor_of_1;
            doDFS(vertex2);
        }
    }
}

//doDFS2
void doDFS2(Vertex* vertex)
{
    int size = vertex->adjacents.size();
   
    for (int i = 0; i < size; i++)
    {
        Vertex* vertex2 = vertex->adjacents[i];
        if (vertex->color == ancestor_of_2)
        {
            if (vertex2->color == not_ancestor)
            {
                vertex2->color = ancestor_of_2;
                doDFS2(vertex2);
            }
            else if (vertex2->color == ancestor_of_1)
            {
                vertex2->color = lowest_a_b;
                doDFS2(vertex2);
            }
        }
        else
        {
            int color_v2 = vertex2->color;
            vertex2->color = ancestor_of_both;
            if (color_v2 == ancestor_of_1)
                doDFS2(vertex2);
        }
    }
}

//lca
void lca()
{
    int output = wrong;
    int size = all_Vertex.size();
    for (int i = 0; i < size; i++)
    {
        Vertex* vertex = all_Vertex[i];
        if (vertex->color == lowest_a_b)
        {
            output = correct;
            cout << (i + 1) << " ";
        }
    }

    if (output == correct)
    {
        cout << endl;
    }
    else
    {
        cout << "-" << endl;
    }
}

//Main
int main()
{
    ios::sync_with_stdio(false);
    int v1, v2;
    int edges_number, vertex_number;
    int x, y;
     
    if (cin >> v1 >> v2 && cin >> vertex_number >> edges_number)
    {}
    else 
    {
        return 0;
    }

    auto start = std::chrono::system_clock::now();
    time_t start_time = std::chrono::system_clock::to_time_t(start);
    cout << "start computation at " << std::ctime(&start_time);

    for (int i = 0; i < vertex_number; i++)
    {
        Vertex* vertex = new Vertex{i + 1, not_ancestor, {}, {}};
        all_Vertex.push_back(vertex);
    }

    for (int i = 0; i < edges_number; i++)
    {
        if (cin >> x >> y)
        {   
            Vertex* vertex = all_Vertex[y - 1];
            if (x >= 1 && x <= vertex_number && y >= 1 && y <= vertex_number)
            { 
                int size = vertex->adjacents.size();
                for (int i = 0; i < size; i++)
                {
                    if (vertex->adjacents[i] == all_Vertex[x - 1])
                    {
                        cout << "0" << endl;
                        return 0;
                    }
                }
                vertex->adjacents.push_back(all_Vertex[x - 1]);
            }
            else
            {
                cout << "0" << endl;
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    
    if (isCyclic())
    {
        cout << "0" << endl;
        return 0;
    }
    else
    {
        doDFS(all_Vertex[v1 - 1]);
        all_Vertex[v2 - 1]->color = all_Vertex[v2 - 1]->color == not_ancestor ? ancestor_of_2 : lowest_a_b;
        doDFS2(all_Vertex[v2 -1]);
        lca();
    }

    for (int i = 0; i < vertex_number; i++)
    {
        delete all_Vertex[i];
    }

    auto end = std::chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << std::ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    return 0;
}