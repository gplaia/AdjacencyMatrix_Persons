//plaia final

/*

Advanced Data Structures and Algorithms Final. May 2020. 

Objective: Create a Graph of people, including their names, workplace, job title, and degree. 

*/

#include<iostream>
#include <queue> 
#include<stack>
#include <string>

using namespace std;

//Person class used to define person objects 
class Person {
public:
	string name; 
	string company; 
	string position; 
	string degree; 
	//default constructor
	Person(){}
	Person(string n, string c, string p, string d)
	{
		name = n; 
		company = c; 
		position = p; 
		degree = d; 
	}
	//setters and getters for access/modifications to Person object variables
	void setName(string n)
	{
		name = n; 
	}
	void setCompany(string c)
	{
		company = c; 
	}
	void setPosition(string p)
	{
		position = p; 
	}
	void setDegree(string d)
	{
		degree = d; 
	}
	string getName()
	{
		return name; 
	}
	string getCompany()
	{
		return company; 
	}
	string getDegree()
	{
		return degree; 
	}
	string getPosition()
	{
		return position; 
	}
};

//each element in the graph will be a node of type Person
class Node {
public:
	Person info;
	Node() {};
	Node(Person x) 
	{ 
		info = x; 
	}
};

//create Adjacency Matrix of all Person Nodes, their data, and connecting edges
class AdjacencyMatrix {
public:
	Node* V;
	int size = -1;
	int last = -1;

	int** M;
	AdjacencyMatrix() {}
	//create matrix
	AdjacencyMatrix(int n) {
		size = n;
		V = new Node[size];
		M = new int*[size];
		for (int i = 0; i < size; i++) {
			M[i] = new int[size];
			for (int j = 0; j < size; j++) {
				M[i][j] = 0;
			}
		}
	}

	//insert a new Person object into the matrix
	void InsertVertex(Person x) {
		Node vertex(x);
		last++;
		V[last] = vertex;
	}

	//insert new edge between Person objects
	void InsertEdge(Person src, Person dest, int weight) {
		int s = Search(src);
		int d = Search(dest);
		//M[s][d] = weight;
		//undirected 
		M[s][d] = 1; 
		M[d][s] = 1; 
	}

	//search for a specific Person object in graph
	int Search(Person key) {
		for (int i = 0; i <= last; i++) {
			//check first names
			if (V[i].info.getName() == key.getName()) return i;
		}
		return -1;
	}

	void BFT(Person key) {
		int start = Search(key);
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) { visited[i] = 0; }

		queue <int> q;
		visited[start] = true;
		q.push(start);

		cout << "-----------Breadth First Traversal----------" << endl;
		while (!q.empty()) {
			start = q.front();
			q.pop();

			cout << start << " | " << V[start].info.getName() << " " << V[start].info.getCompany() << " " << V[start].info.getPosition() << " " << V[start].info.getDegree() << endl;
			for (int i = 0; i < size; i++) {
				if (M[start][i] > 0 && !visited[i]) {
					visited[i] = true;
					q.push(i);
				}
			}
		}
		cout << "---------------------------------------" << endl;
	}

	void DFT(Person key) {
		int start = Search(key);
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) { visited[i] = 0; }

		stack <int> s;
		visited[start] = true;
		s.push(start);

		cout << "-----------Depth First Traversal------------" << endl;
		while (!s.empty()) {
			start = s.top();
			s.pop();
			cout << start << " | " << V[start].info.getName() << " " << V[start].info.getCompany() << " " << V[start].info.getPosition() << " " << V[start].info.getDegree() << endl;

			for (int i = 0; i < size; i++) {
				if (M[start][i] > 0 && !visited[i]) {
					visited[i] = true;
					s.push(i);
				}
			}
		}
		cout << "-----------------------------------" << endl;
	}

};

int main() {

	AdjacencyMatrix* matrix = new AdjacencyMatrix(5);

	Person p1 = { "Gabriella", "company", "manager", "math" };
	Person p2 = { "Kayla", "company", "manager", "math" }; 
	Person p3 = { "fahad", "company", "manager", "math" }; 
	Person p4 = { "andy", "company", "manager", "math" }; 
	Person p5 = { "tiff", "company", "manager", "math" };
	
	matrix->InsertVertex(p1);
	matrix->InsertVertex(p2);
	matrix->InsertVertex(p3);
	matrix->InsertVertex(p4);
	matrix->InsertVertex(p5);


	matrix->InsertEdge(p1 ,p2, 1);//gab and kayla
	matrix->InsertEdge(p2, p3, 1);//kayla and fahad 
	matrix->InsertEdge(p3, p4, 1);//fahad and andy
	matrix->InsertEdge(p4, p5, 1);//andy and tiff
	matrix->InsertEdge(p5, p2, 1);//tiff and kayla
	matrix->InsertEdge(p4, p1, 1);//andy and gab
	matrix->InsertEdge(p1, p3, 1);//gab and fahad 

	matrix->BFT(p1);//starting at Gab
	matrix->DFT(p2);//starting at kayla

	system("pause"); 
	return 0;
}