# Health Diagnosis Decision Tree

This project implements a simple health diagnosis system using a decision tree algorithm in C++. Given a set of symptoms, the program predicts the most likely disease and suggests other possible diseases based on symptom matching.

## Features

- Builds a decision tree from a dataset of diseases and their associated symptoms.
- Diagnoses the most likely disease based on user-input symptoms.
- Provides a list of other possible diseases ranked by the number of matching symptoms.
- Implements entropy and information gain to build an optimized decision tree.

## Technologies Used

- C++ (Standard Library)
- Basic data structures: maps, vectors, sets
- Concepts of decision trees, entropy, and information gain

## Usage

1. Compile the code with a C++ compiler (e.g., `g++ main.cpp -o diagnosis`).
2. Run the executable (`./diagnosis` or `diagnosis.exe`).
3. Enter symptoms separated by commas when prompted.
4. View the predicted disease and other possible diseases.

## Example
Enter symptoms (comma-separated): cough, fever, fatigue

Most likely disease: COVID-19
Other possible diseases:
Flu (3 matching symptoms)
Pneumonia (3 matching symptoms)
Bronchitis (2 matching symptoms)


## Dataset

The project uses a predefined dataset of diseases and their common symptoms, including:

- Allergy
- Anemia
- Asthma
- Bronchitis
- Chickenpox
- COVID-19
- Dengue
- Diabetes
- Flu
- Hypertension
- Hypothyroidism
- Malaria
- Migraine
- Pneumonia
- Tuberculosis

## How it Works

The decision tree is built using entropy and information gain to find the symptom that best splits the diseases. The tree is traversed based on the presence or absence of symptoms to arrive at a diagnosis.

## Future Improvements

- Expand the dataset with more diseases and symptoms.
- Add a graphical user interface for easier interaction.
- Integrate with a web or mobile app.
- Improve diagnosis accuracy with machine learning techniques.

## License

This project is open-source and available under the MIT License.

---

Feel free to contribute or raise issues!



