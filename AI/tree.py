import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn import metrics
import joblib
import sys

# Function to train the Decision Tree Classifier and save it to a file
# def train_and_save_classifier():
#     col_names = ['pulse', 'body_temperature', 'spO2', 'status']
#     # load dataset
#     pima = pd.read_csv("Health data.csv", header=0, names=col_names)

#     feature_cols = ['pulse', 'body_temperature', 'spO2']
#     X = pima[feature_cols]  # Features
#     y = pima.status  # Target variable

#     # Split dataset into training set and test set
#     X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)  # 70% training and 30% test

#     # Create Decision Tree classifer object
#     clf = DecisionTreeClassifier()

#     # Train Decision Tree Classifer
#     clf = clf.fit(X_train.values, y_train.values)

#     # Save the trained classifier to a file
#     joblib.dump(clf, 'health_classifier.pkl')

#Function to load the trained classifier and make predictions
def load_classifier_and_predict(pulse, temp, saturation):
    
    clf = joblib.load('health_classifier.pkl')
    prediction = int(clf.predict([[pulse, temp, saturation]]))
    return prediction
    


if __name__ == "__main__":

    #train_and_save_classifier()

    pulse = float(sys.argv[1])
    temp = float(sys.argv[2])
    saturation = float(sys.argv[3])

    predicted_health_status = load_classifier_and_predict(pulse, temp, saturation)
    print(predicted_health_status)

