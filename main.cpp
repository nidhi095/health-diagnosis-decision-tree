int main() {
    map<string, vector<string>> diseaseSymptoms = {
        {"Allergy", {"itching", "rash", "runny_nose", "sneezing"}},
        {"Anemia", {"fatigue", "paleness", "shortness_of_breath"}},
        {"Asthma", {"chest_tightness", "cough", "shortness_of_breath"}},
        {"Bronchitis", {"cough", "fatigue", "shortness_of_breath"}},
        {"Chickenpox", {"fatigue", "fever", "muscle_pain", "rash"}},
        {"COVID-19", {"cough", "fever", "fatigue", "loss_of_taste"}},
        {"Dengue", {"fever", "headache", "muscle_pain", "rash"}},
        {"Diabetes", {"blurred_vision", "fatigue", "frequent_urination", "weight_loss"}},
        {"Flu", {"cough", "fatigue", "fever", "sore_throat"}},
        {"Hypertension", {"blurred_vision", "dizziness", "headache"}},
        {"Hypothyroidism", {"cold_intolerance", "fatigue", "weight_gain"}},
        {"Malaria", {"chills", "fever", "headache", "sweating"}},
        {"Migraine", {"headache", "nausea", "sensitivity_to_light"}},
        {"Pneumonia", {"chest_pain", "cough", "fever", "shortness_of_breath"}},
        {"Tuberculosis", {"cough", "fever", "night_sweats", "weight_loss"}}
    };

    DecisionTree dt(diseaseSymptoms);

    cout << "Enter symptoms (comma-separated): ";
    string input;
    getline(cin, input);

    vector<string> inputSymptoms;
    stringstream ss(input);
    string symptom;
    while (getline(ss, symptom, ',')) {
        symptom.erase(remove(symptom.begin(), symptom.end(), ' '), symptom.end());
        inputSymptoms.push_back(symptom);
    }

    string diagnosed = dt.diagnose(inputSymptoms);
    cout << "\nMost likely disease: " << diagnosed << "\n";

    vector<pair<string,int>> others = dt.getSimilarDiseases(inputSymptoms);
    cout << "Other possible diseases:\n";
    for (auto& [d, count] : others) {
        if (d != diagnosed)
            cout << "- " << d << " (" << count << " matching symptoms)\n";
    }

    return 0;
}



