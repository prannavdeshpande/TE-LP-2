def calculate_bmi(weight, height_cm):
    """Calculate BMI (kg/m²) and round to 1 decimal place. Ref: WHO BMI classification."""
    if height_cm <= 0:
        raise ValueError("Height must be positive")
    height_m = height_cm / 100
    bmi = weight / (height_m ** 2)
    return round(bmi, 1)

def evaluate_hypertension(systolic, diastolic, symptoms):
    """Evaluate hypertension risk based on BP and symptoms. Ref: AHA guidelines."""
    hypertension_risk = False
    if systolic >= 140 or diastolic >= 90:
        hypertension_risk = True
        print("🩺 Diagnosis: Hypertension (High Blood Pressure).")
        if symptoms['chest_pain'] == 'yes':
            print("⚠️ Chest pain reported. Seek immediate medical attention.")
        if symptoms['headache'] == 'yes':
            print("⚠️ Frequent headaches may indicate vascular stress.")
        print("📝 Suggestion: Reduce salt intake, monitor BP regularly, consult a cardiologist.\n")
    elif 120 <= systolic < 140 or 80 <= diastolic < 90:
        hypertension_risk = True
        print("🩺 Diagnosis: Pre-hypertension stage.")
        print("📝 Suggestion: Adopt lifestyle changes (e.g., exercise, diet). Monitor BP.\n")
    else:
        print("✅ Blood pressure is within normal range.\n")
    return hypertension_risk

def general_symptom_check(diabetes_risk, hypertension_risk, symptoms):
    """Check for mild symptoms and provide warnings if risks are low."""
    mild_warning = False
    if any(symptom == 'yes' for symptom in [symptoms['frequent_thirst'], symptoms['frequent_urination'], 
                                            symptoms['blurred_vision'], symptoms['fatigue']]):
        mild_warning = True
        print("� geven ⚠️ Mild symptoms detected despite normal readings.")
        print("📝 Suggestion: Consult a doctor for further evaluation.\n")
    elif symptoms['chest_pain'] == 'yes' or symptoms['headache'] == 'yes':
        mild_warning = True
        print("⚠️ Chest pain or headache detected without hypertension.")
        print("📝 Suggestion: Consider stress evaluation or ECG. Consult a physician.\n")
    else:
        print("✅ No concerning symptoms detected.\n")
    return mild_warning

def evaluate_diabetes_risk_score(fasting_sugar, post_meal_sugar, history_diabetes, symptom_count):
    """Calculate diabetes risk score. Ref: ADA diabetes criteria."""
    score = 0
    if fasting_sugar >= 126:
        score += 2
    if post_meal_sugar >= 200:
        score += 2
    if history_diabetes == 'yes':
        score += 1
    if symptom_count > 0:
        score += 1
    if score >= 4:
        return "High"
    elif score >= 2:
        return "Moderate"
    else:
        return "Low"

def evaluate_diabetes(fasting, post_meal, history, symptoms):
    """Evaluate diabetes risk based on sugar levels, history, and symptoms."""
    symptom_count = sum(1 for value in symptoms.values() if value == 'yes')
    risk_level = evaluate_diabetes_risk_score(fasting, post_meal, history, symptom_count)
    print(f"🧪 Diabetes Risk Level: {risk_level}")
    diabetes_risk = False

    if fasting >= 126 or post_meal >= 200:
        diabetes_risk = True
        print("🩺 Diagnosis: Likely diabetic.")
        if history == 'yes':
            print("➡️ Note: Family history of diabetes with critically high levels.")
        else:
            print("➡️ Warning: Diabetic levels detected without prior history.")
        print("📝 Suggestion: Consult a diabetologist. Start sugar control measures.\n")
    elif 100 <= fasting < 126 or 140 <= post_meal < 200:
        diabetes_risk = True
        print("🩺 Diagnosis: Pre-diabetic stage.")
        print("📝 Suggestion: Control diet, increase exercise, monitor monthly.\n")
    elif symptom_count > 0 and (fasting > 110 or post_meal > 160):
        diabetes_risk = True
        print("🩺 Diagnosis: Symptoms with elevated sugar suggest early diabetes.")
        print("📝 Suggestion: Perform HbA1c test and consult a physician.\n")
    else:
        print("✅ Blood sugar levels are within safe range.\n")
    
    return diabetes_risk

def final_summary(age, diabetes_risk, hypertension_risk, mild_warning):
    """Provide a final health summary based on risks and age."""
    if not diabetes_risk and not hypertension_risk and not mild_warning:
        print("✅ You are in good health based on provided inputs.")
        if age > 45:
            print("🔄 Age over 45: Regular health checkups recommended.\n")
        else:
            print("💪 Maintain your healthy lifestyle!\n")
    elif mild_warning and not diabetes_risk and not hypertension_risk:
        print("⚠️ Mild symptoms detected but no major risks identified.")
        print("📝 Suggestion: Monitor symptoms and consult a doctor if they persist.\n")
    print("======= END OF REPORT =======")

def get_numeric_input(prompt, input_type, min_value=None, max_value=None):
    """Helper function to get and validate numeric input."""
    while True:
        try:
            value = input_type(input(prompt))
            if min_value is not None and value < min_value:
                print(f"Value must be at least {min_value}. Try again.")
                continue
            if max_value is not None and value > max_value:
                print(f"Value must be at most {max_value}. Try again.")
                continue
            return value
        except ValueError:
            print("Invalid input. Please enter a valid number.")

def get_yes_no_input(prompt):
    """Helper function to get and validate yes/no input."""
    while True:
        value = input(prompt).lower()
        if value in ('yes', 'y'):
            return 'yes'
        elif value in ('no', 'n'):
            return 'no'
        print("Invalid input. Please enter 'yes' or 'no'.")

def main():
    """Main function to run the medical expert system."""
    print("===============================================")
    print("      ADVANCED MEDICAL EXPERT SYSTEM           ")
    print(" Focus Areas: Diabetes, Hypertension, General Risk")
    print("===============================================\n")

    # Get and validate inputs
    age = get_numeric_input("Enter your age: ", int, min_value=1, max_value=120)
    weight = get_numeric_input("Enter your weight (in kg): ", float, min_value=1, max_value=500)
    height = get_numeric_input("Enter your height (in cm): ", float, min_value=50, max_value=300)
    fasting_sugar = get_numeric_input("Enter fasting blood sugar level (mg/dL): ", float, min_value=0, max_value=1000)
    post_meal_sugar = get_numeric_input("Enter post-meal blood sugar level (mg/dL): ", float, min_value=0, max_value=1000)
    systolic_bp = get_numeric_input("Enter systolic BP (upper number): ", int, min_value=50, max_value=300)
    diastolic_bp = get_numeric_input("Enter diastolic BP (lower number): ", int, min_value=30, max_value=200)
    history_diabetes = get_yes_no_input("Do you have a history of diabetes? (yes/no): ")

    symptoms = {
        'frequent_thirst': get_yes_no_input("Do you often feel thirsty? (yes/no): "),
        'frequent_urination': get_yes_no_input("Do you urinate frequently? (yes/no): "),
        'blurred_vision': get_yes_no_input("Do you have blurred vision? (yes/no): "),
        'fatigue': get_yes_no_input("Do you feel tired often? (yes/no): "),
        'chest_pain': get_yes_no_input("Do you experience chest pain? (yes/no): "),
        'headache': get_yes_no_input("Do you experience frequent headaches? (yes/no): ")
    }

    print("\n======= DIAGNOSIS REPORT =======\n")
    bmi = calculate_bmi(weight, height)
    print(f"📊 Your BMI is: {bmi} - ", end="")
    if bmi < 18.5:
        print("Underweight")
    elif 18.5 <= bmi < 24.9:
        print("Normal (Good)")
    elif 25 <= bmi < 29.9:
        print("Overweight")
    else:
        print("Obese")
    print()

    diabetes_risk = evaluate_diabetes(fasting_sugar, post_meal_sugar, history_diabetes, symptoms)
    hypertension_risk = evaluate_hypertension(systolic_bp, diastolic_bp, symptoms)
    mild_warning = general_symptom_check(diabetes_risk, hypertension_risk, symptoms)
    final_summary(age, diabetes_risk, hypertension_risk, mild_warning)

if __name__ == "__main__":
    main()