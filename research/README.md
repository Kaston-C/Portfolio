# Intelligent Intent Recognition Research

This project focuses on predicting human gait patterns during different types of movement, including level-walking, ramp ascent and descent, and stair ascent and descent. The goal is to improve the accuracy of intent recognition, ensuring that the model performs well enough for real-time use in practical applications. In real-world settings, 99.9% accuracy can still result in one or two major falls, given that individuals take thousands of strides daily.

## Research Overview

### Goals:
- Increase the accuracy of intent recognition while ensuring the model is fast enough for real-time use.
- Minimizing prediction errors, as even small errors can lead to significant consequences (e.g., falls).
- Continue refining model performance to ensure practical, reliable predictions for everyday activities.

### Methodology:
We use a **Temporal Convolutional Network (TCN)** model to predict gait patterns, with the following primary focuses:
- **User-Independent Models**: Models that do not rely on specific user data.
- **User-Dependent Models**: Models trained specifically for individual users.
- **Semi-Dependent Models**: A hybrid approach that includes both user-specific and generalized data.
 
*Through our experiments, we've found that semi-dependent models offer the best performance, and they are now the primary focus of our work.*

### Current Focus:
- Testing varying slope change timing to understand its impact on prediction accuracy.
- Preparing to integrate **intact thigh IMU data** (Inertial Measurement Unit) into the model to improve performance.

## Model Training and Testing

The training and testing process follows these steps:

1. **Training**: 
   - The model is trained on labeled gait data from different conditions (e.g., level walking, ramp ascent/descent, stair ascent/descent). 
   - We use a combination of supervised learning and cross-validation to ensure the model generalizes well to unseen data.
   - The focus is on training semi-dependent models, which have proven to provide the best balance of user specificity and generalization.

2. **Testing**: 
   - After training, the model is tested on a separate dataset to assess its performance. This involves evaluating its accuracy in real-world conditions, focusing on metrics such as precision, recall, and F1 score. 
   - Special attention is given to minimizing false positives and false negatives, as even minor misclassifications can have significant real-world consequences, such as falls.
   - #### Statistical Visualization:
     - To better understand model performance, we use statistical analysis methods, including p-values and confidence intervals, to quantify the reliability of the results. Performance is visualized using **MAE (Mean Absolute Error) Bar Charts**, which help highlight overall model performance across different conditions.

3. **Optimization for Real-Time Use**: 
   - We prioritize keeping the model efficient enough to run in real-time, without compromising prediction accuracy. This involves testing different model configurations and optimizing the code to ensure it meets real-time processing requirements.
   - We switched from using **XGBoost** to **Temporal Convolutional Networks (TCNs)** because TCNs offer a significant speed increase, enabling real-time predictions without sacrificing accuracy.

## Team Structure

The research team is divided into three subteams:

1. **Machine Learning (ML)**: Focuses on model development, training, and testing.  
   *Current work includes optimizing semi-dependent models, ensuring real-time performance, and visualizing results using statistical methods.*

2. **Development**: Focuses on hardware, ensuring the proper setup for experimentation and data collection.

3. **Biomechanics**: Focuses on data collection and processing. This team gathers and prepares the data needed for training the models.

## Leadership

The research team is co-led by two undergraduates, including myself. We oversee high-level tasks, such as:
- Coordinating meeting times.
- Preparing and presenting slideshows.
- Ensuring effective communication between subteams.
