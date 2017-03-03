#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <limits>
#include <stack>
using namespace std;

typedef long long ll;
struct Node{
    bool visited = false;
    ll distance=numeric_limits<ll>::max();
    vector<pair<ll,ll>> neighbors;
    ll value;
    ll parent=-1;
};

struct node_cmp
{
    bool operator()( const Node* a, const Node* b ) const
    {
        return a->distance > b->distance;
    }
};

vector<Node> vertices;

void dijkstra(Node* root, priority_queue<Node*, vector<Node*>, node_cmp>* q){
    root->visited = true;
    for(int i=0; i<root->neighbors.size(); i++){
        if(root->distance + root->neighbors[i].second < vertices[root->neighbors[i].first].distance){
            vertices[root->neighbors[i].first].distance =root->distance + root->neighbors[i].second;
            vertices[root->neighbors[i].first].parent = root->value;
            q->push(&vertices[root->neighbors[i].first]);
        }
    }
    q->pop();
}

int main(){
    ll v,e;
    cin >> v;
    cin >> e;
    vertices.resize(v+1);
    for(ll i=1; i<=v; i++){
        vertices[i].value = i;
    }
    for(ll i=0; i<e; i++){
        ll first;
        ll second;
        ll cost;
        cin >> first;
        cin >> second;
        cin >> cost;
        vertices[first].neighbors.push_back(make_pair(second,cost));
        vertices[second].neighbors.push_back(make_pair(first,cost));
    }
    vertices[1].distance = 0;
    vertices[1].parent = 1;
    priority_queue<Node*, vector<Node*>, node_cmp> pq;
    pq.push(&vertices[1]);
    while(!pq.empty()){
        dijkstra(pq.top(), &pq);
    }
    if(vertices[v].parent == -1){
        cout <<-1;
        return 0;
    }
    Node* temp = &vertices[v];
   	stack<int> output;
   	while(temp->value!=1){
        output.push(temp->value);
        temp = &vertices[temp->parent];
   	}
   	output.push(temp->value);
   	while(!output.empty()){
        cout << output.top() << " ";
        output.pop();
   	}
    return 0;
}