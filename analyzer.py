import string
import secrets

def analyze_and_generate_password():
    print("=" * 45)
    print("   SECURE PASSWORD GENERATOR & ANALYZER   ")
    print("=" * 45)

    # 1. Real-World Password Analyzer
    user_password = input("Enter a password to test its strength: ").strip()
    
    # Check length
    length = len(user_password)
    has_upper = any(c.isupper() for c in user_password)
    has_lower = any(c.islower() for c in user_password)
    has_digit = any(c.isdigit() for c in user_password)
    has_special = any(c in string.punctuation for c in user_password)

    # Calculate score metrics
    score = 0
    feedback = []

    if length >= 12: score += 2
    elif length >= 8: score += 1
    else: feedback.append("- Password is too short (aim for at least 12 characters).")

    if has_upper: score += 1
    else: feedback.append("- Missing uppercase letters.")

    if has_lower: score += 1
    else: feedback.append("- Missing lowercase letters.")

    if has_digit: score += 1
    else: feedback.append("- Missing numeric digits.")

    if has_special: score += 1
    else: feedback.append("- Missing special characters (e.g., !, @, #).")

    # Display evaluation results
    print("\n--- Strength Report ---")
    if score >= 5:
        print("Strength Rating: STRONG 🔥")
    elif score >= 3:
        print("Strength Rating: MEDIUM ⚠️")
    else:
        print("Strength Rating: WEAK ❌")

    if feedback:
        print("Vulnerabilities Found:")
        for item in feedback:
            print(item)
    else:
        print("Excellent! Your password meets all security rules.")

    # 2. Cryptographically Secure Generator Engine
    print("\n" + "-" * 45)
    print("Generate a secure replacement alternative:")
    try:
        desired_length = int(input("Enter desired password length (minimum 12): "))
        if desired_length < 12:
            print("Notice: Forcing minimum length to 12 for strong real-world safety.")
            desired_length = 12
    except ValueError:
        desired_length = 14

    # Build reliable pool using standard character matrices
    character_pool = string.ascii_letters + string.digits + "!@#$%^&*()-_=+"
    
    # Guarantee at least one character from each critical group to satisfy rules
    guaranteed_chars = [
        secrets.choice(string.ascii_lowercase),
        secrets.choice(string.ascii_uppercase),
        secrets.choice(string.digits),
        secrets.choice("!@#$%^&*()-_=+")
    ]
    
    # Fill out the remaining requested length randomly
    remaining_length = desired_length - len(guaranteed_chars)
    random_chars = [secrets.choice(character_pool) for _ in range(remaining_length)]
    
    # Combine lists and safely shuffle using cryptographically sound sorting methods
    final_password_list = guaranteed_chars + random_chars
    
    # Cryptographically secure shuffle trick
    secure_shuffled = sorted(final_password_list, key=lambda k: secrets.randbelow(100000))
    generated_password = "".join(secure_shuffled)

    print(f"\nGenerated Secure Password:\n👉  {generated_password}  👈")
    print("-" * 45)

if __name__ == "__main__":
    analyze_and_generate_password()
