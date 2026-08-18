#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 1. Concrete Flyweight (Stores Intrinsic State)
class TreeType {
private:
    string name;
    string color;
    string texture; // Heavy resource data representation

public:
    TreeType(string n, string c, string t) : name(n), color(c), texture(t) {}

    void draw(int x, int y) {
        cout << "Drawing tree [" << name << " | Color: " << color 
             << " | Texture: " << texture << "] at coordinates (" << x << ", " << y << ")\n";
    }
};

// 2. Flyweight Factory
class TreeFactory {
private:
    static unordered_map<string, TreeType*> treeTypes;

public:
    static TreeType* getTreeType(string name, string color, string texture) {
        string key = name + "_" + color + "_" + texture;
        if (treeTypes.find(key) == treeTypes.end()) {
            treeTypes[key] = new TreeType(name, color, texture);
            cout << "--> [Factory] Creating NEW shared TreeType: " << key << "\n";
        } else {
            cout << "--> [Factory] Reusing EXISTING shared TreeType: " << key << "\n";
        }
        return treeTypes[key];
    }

    static void cleanup() {
        for (auto pair : treeTypes) {
            delete pair.second;
        }
        treeTypes.clear();
    }
};

// Initialize static member
unordered_map<string, TreeType*> TreeFactory::treeTypes;

// 3. Context Object (Contains Extrinsic State + Reference to Flyweight)
class Tree {
private:
    int x;
    int y;
    TreeType* type; // Shared intrinsic flyweight reference

public:
    Tree(int xCoord, int yCoord, TreeType* treeType) : x(xCoord), y(yCoord), type(treeType) {}

    void draw() {
        type->draw(x, y);
    }
};

// 4. Forest Client
class Forest {
private:
    vector<Tree*> trees;

public:
    void plantTree(int x, int y, string name, string color, string texture) {
        TreeType* type = TreeFactory::getTreeType(name, color, texture);
        Tree* tree = new Tree(x, y, type);
        trees.push_back(tree);
    }

    void draw() {
        for (auto tree : trees) {
            tree->draw();
        }
    }

    ~Forest() {
        for (auto tree : trees) {
            delete tree;
        }
    }
};


int main() {
    Forest forest;

    cout << "--- Planting Trees in Forest ---\n";
    // Reuse intrinsic 'Oak' type
    forest.plantTree(10, 20, "Oak", "Green", "OakTexture.png");
    forest.plantTree(15, 25, "Oak", "Green", "OakTexture.png");

    // Reuse intrinsic 'Pine' type
    forest.plantTree(50, 60, "Pine", "Dark Green", "PineTexture.png");
    forest.plantTree(55, 65, "Pine", "Dark Green", "PineTexture.png");

    cout << "\n--- Rendering Forest ---\n";
    forest.draw();

    TreeFactory::cleanup();
    return 0;
}
