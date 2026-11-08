# Main Runner

from hospital_management import HospitalManagementSystem
from library_management import LibraryManagementSystem
from inventory_management import InventoryManagementSystem
from password_analyzer import PasswordAnalyzer
from tic_tac_toe import TicTacToeGame
from snake_game import SnakeGame
from word_guessing_game import WordGuessingGame


def run_hospital_system() -> None:
    hospital = HospitalManagementSystem()
    hospital.add_doctor("D001", "Dr. Ayesha Khan", "Cardiology")
    hospital.add_patient("P001", "Nawaz Ali", 35, "Chest pain", "ICU-01")
    hospital.schedule_appointment("A001", "P001", "D001", "2026-11-09 09:00")
    print("Hospital system demo:")
    print(hospital.dashboard())


def run_library_system() -> None:
    library = LibraryManagementSystem()
    library.add_book("B001", "Python in Practice", "Ali Khan", "Programming", 2)
    library.register_member("M001", "Zara", "zara@example.com")
    print("Library system demo:")
    print(library.issue_book("M001", "B001"))


def run_inventory_system() -> None:
    inventory = InventoryManagementSystem()
    inventory.add_product("SKU01", "Keyboard", "Electronics", 45.00, 20, 8)
    inventory.sell_product("SKU01", 2)
    print("Inventory system demo:")
    print(inventory.generate_report())


def run_password_checks() -> None:
    print("Password analyzer demo:")
    for password in ["Admin123!", "hello123", "Str0ngPass#2026"]:
        result = PasswordAnalyzer.evaluate(password)
        print(result.strength, result.score, result.suggestions)


def run_tic_tac_toe() -> None:
    game = TicTacToeGame()
    game.play()


def run_snake_game() -> None:
    SnakeGame().run()


def run_word_game() -> None:
    WordGuessingGame().play()


def main() -> None:
    while True:
        print("\n=== Project Menu ===")
        print("1. Hospital Management System")
        print("2. Library Management System")
        print("3. Inventory Management System")
        print("4. Password Analyzer")
        print("5. Tic Tac Toe")
        print("6. Snake Game")
        print("7. Word Guessing Game")
        print("8. Exit")

        choice = input("Select option: ").strip()

        if choice == "1":
            run_hospital_system()
        elif choice == "2":
            run_library_system()
        elif choice == "3":
            run_inventory_system()
        elif choice == "4":
            run_password_checks()
        elif choice == "5":
            run_tic_tac_toe()
        elif choice == "6":
            run_snake_game()
        elif choice == "7":
            run_word_game()
        elif choice == "8":
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Try again.")


if __name__ == "__main__":
    main()
