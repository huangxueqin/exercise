#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

class disj_set {
private:
    size_t n;
    int *parent;
public:
    disj_set(int size) : n(size) {
        parent = (int *) malloc(n * sizeof(int));
        for(size_t i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int merge(int x, int y) {
        if(find(x) != find(y)) {
            parent[x[parent]] = parent[y];
        }
        return parent[y];
    }

    ~disj_set() {
        if(parent != null) {
            free(parent);
        }
    }
};

int main(void) {
}
