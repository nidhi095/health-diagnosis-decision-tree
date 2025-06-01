/ Tree node for decision tree
struct TreeNode {
    string symptom; // symptom to check at this node
    string disease; // disease if leaf node (empty if not leaf)
    TreeNode* left; // symptom absent
    TreeNode* right; // symptom present

    TreeNode(string s) : symptom(s), disease(""), left(nullptr), right(nullptr) {}
    TreeNode(string s, bool leaf) : symptom(""), disease(s), left(nullptr), right(nullptr) {}
};

class DecisionTree {
public:
    DecisionTree(const map<string, vector<string>>& data) : diseaseSymptoms(data) {
        buildTree();
    }

    string diagnose(const vector<string>& inputSymptoms) {
        TreeNode* node = root;
        while (node && node->disease == "") {
            bool hasSymptom = (find(inputSymptoms.begin(), inputSymptoms.end(), node->symptom) != inputSymptoms.end());
            node = hasSymptom ? node->right : node->left;
        }
        return node ? node->disease : "Disease Unknown";
    }

    // For "other possible diseases" sorting by symptom match count
    vector<pair<string,int>> getSimilarDiseases(const vector<string>& inputSymptoms) {
        vector<pair<string,int>> matches;
        for (auto& [disease, symptoms] : diseaseSymptoms) {
            int count = 0;
            for (auto& s : inputSymptoms) {
                if (find(symptoms.begin(), symptoms.end(), s) != symptoms.end())
                    count++;
            }
            if (count > 0) matches.push_back({disease, count});
        }
        mergeSort(matches, 0, matches.size()-1);
        return matches;
    }

private:
    map<string, vector<string>> diseaseSymptoms;
    TreeNode* root;

    void buildTree() {
        // Gather all symptoms
        set<string> allSymptoms;
        for (auto& [disease, symptoms] : diseaseSymptoms) {
            for (auto& s : symptoms)
                allSymptoms.insert(s);
        }
        vector<string> symptomsList(allSymptoms.begin(), allSymptoms.end());
        vector<string> diseases;
        for (auto& p : diseaseSymptoms) diseases.push_back(p.first);

        root = buildTreeHelper(diseases, symptomsList);
    }

    TreeNode* buildTreeHelper(const vector<string>& diseases, const vector<string>& symptoms) {
        if (diseases.size() == 1) {
            return new TreeNode(diseases[0], true); // Leaf node with disease
        }
        if (symptoms.empty()) {
            // If no symptoms left, pick the first disease (could be improved)
            return new TreeNode(diseases[0], true);
        }

        // Find best symptom to split on (max info gain)
        double bestGain = -1;
        string bestSymptom;
        vector<string> leftDiseases, rightDiseases;

        for (auto& symptom : symptoms) {
            vector<string> leftSet, rightSet;
            for (auto& d : diseases) {
                if (hasSymptom(d, symptom)) rightSet.push_back(d);
                else leftSet.push_back(d);
            }
            double gain = informationGain(diseases, leftSet, rightSet);
            if (gain > bestGain) {
                bestGain = gain;
                bestSymptom = symptom;
                leftDiseases = leftSet;
                rightDiseases = rightSet;
            }
        }

        if (bestGain <= 0) {
            // Can't split better, return most common disease
            return new TreeNode(mostCommonDisease(diseases), true);
        }

        vector<string> remainingSymptoms;
        for (auto& s : symptoms)
            if (s != bestSymptom) remainingSymptoms.push_back(s);

        TreeNode* node = new TreeNode(bestSymptom);
        node->left = buildTreeHelper(leftDiseases, remainingSymptoms);
        node->right = buildTreeHelper(rightDiseases, remainingSymptoms);
        return node;
    }

    bool hasSymptom(const string& disease, const string& symptom) {
        auto it = diseaseSymptoms.find(disease);
        if (it == diseaseSymptoms.end()) return false;
        return find(it->second.begin(), it->second.end(), symptom) != it->second.end();
    }

    double entropy(const vector<string>& diseases) {
        map<string,int> freq;
        for (auto& d : diseases) freq[d]++;
        double ent = 0.0;
        int total = diseases.size();
        for (auto& [d, count] : freq) {
            double p = (double)count / total;
            ent -= p * log2(p);
        }
        return ent;
    }

    double informationGain(const vector<string>& parent,
                           const vector<string>& left,
                           const vector<string>& right) {
        double parentEntropy = entropy(parent);
        double leftEntropy = entropy(left);
        double rightEntropy = entropy(right);
        double leftWeight = (double)left.size() / parent.size();
        double rightWeight = (double)right.size() / parent.size();
        return parentEntropy - (leftWeight * leftEntropy + rightWeight * rightEntropy);
    }

    string mostCommonDisease(const vector<string>& diseases) {
        map<string,int> freq;
        for (auto& d : diseases) freq[d]++;
        string best;
        int maxCount = 0;
        for (auto& [d, count] : freq) {
            if (count > maxCount) {
                maxCount = count;
                best = d;
            }
        }
        return best;
    }
