//RESTAURANT'S BOILED FISH PROBLEM

//Question:
//n people queue up everyday to purchase the Restaurant's Boiled Fish. 
//The i-th person in line wants to buy ai servings of the dish.
//The chef prepares q batches of the dish - the j-th batch has kj servings of Boiled Fish. 
//Once a batch is ready,
//it is given one by one to the person standing at the front of the queue.
//The instant a person receives as many servings as they wanted,
//they immediately leave the queue
//(and so the next serving is given to the next person in line till they leave, and so on).
//After the n-th person has been served,
//any remaining servings from that batch are thrown out and the restaurant is cleaned.
//However, as the Restaurant is quite popular - when the restaurant is being cleaned,
//the same n people line up once again - in the exact same order,
//and with exactly the same requirements as before.
//This process continues as long as the chef continues to make batches.
//Your task is to tell the chef how many people remain
//in the queue after each batch of Boiled Fish is served.
//Note that once the n-th person has been served, 
//all n people queue up again, 
//so your output in this case should be n and not 0.

//input:
//the first line contains 
//two integers n and q (1 ≤ n, q ≤ 200000) - the number of
//customers and the number of customers and the number of batches prepared by the chef. 
//the second line contains 
//n integers a1, a2, a3... , an (1 ≤ ai ≤ 10^9 ) - the number of
//servings required by each customer.
//the third line contains
//q integers k1, k2, k3... , kq (1 ≤ ki ≤ 10^14 ) - ki, is the number of 
//servings prepared in the i-th batch.

//output:
//print q lines, the i-th of which is the number of
//customers remaining after the i-th batch has been served.



//The code is as follows:


#include <iostream>
#include <vector>
using namespace std;
void processServings(vector<long long>& queue, int& currentPerson, long long servings) {
    int n = queue.size();
    while (servings > 0 && currentPerson < n) {
        if (servings >= queue[currentPerson]) {
            servings -= queue[currentPerson];
            currentPerson++;
        } else {
            queue[currentPerson] -= servings;
            servings = 0;
        }}}
void handleQueries(int n, int q, const vector<long long>& servingsRequired, const vector<long long>& servingsProduced) {
    vector<long long> currentQueue = servingsRequired;
    int currentPerson = 0;
    for (int i = 0; i < q; i++) {
        long long remainingServings = servingsProduced[i];
        processServings(currentQueue, currentPerson, remainingServings);
        if (currentPerson == n) {
            cout << n << endl;
            currentPerson = 0;
            currentQueue = servingsRequired;
        } else {
            cout << n - currentPerson << endl;
        }}}
int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> servingsRequired(n);
    for (int i = 0; i < n; i++) {
        cin >> servingsRequired[i];
    }
    vector<long long> servingsProduced(q);
    for (int i = 0; i < q; i++) {
        cin >> servingsProduced[i];
    }
    handleQueries(n, q, servingsRequired, servingsProduced);
    return 0;
}