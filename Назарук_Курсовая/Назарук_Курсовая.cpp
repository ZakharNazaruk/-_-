#include "Header.h"
#include <cctype>

vector<User> vectUser(0);
vector<Toy> vectToy(0);


void GoToXY(short x, short y);
void ConsoleCursorVisible(bool show, short size);
void Green();
void Cyan();
void Purpule();
void UserMenu();
void mainMenu();
void adminMenu();
void sortMenu();
void filtrMenu();
void DisplayToys();

void RemoveToy();
void AddToy();
string Password(string password) {
	Cyan();
	password = "";
	char ch;
	bool ctrlPressed = false;
	GoToXY(55, 12);

	cout << "Введите пароль: ";

	while (true) {
		ch = _getch();
		if (ch == 13) { // 13 - код клавиши Enter
			break;
		}
		if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
			if (password.length() > 0) {
				password.erase(password.length() - 1);
				cout << "\b \b"; // удаляем последнюю звездочку
			}
		}
		else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
			if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
				if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
					continue; // игнорируем клавиши сочетания
				}
			}
			password += ch;
			cout << '*';
		}
		else if (ch == -32) { // игнорируем коды направлений стрелок
			ch = _getch(); // считываем второй байт кода клавиши
			if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
				continue; // игнорируем стрелки
			}
		}
		else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
			ctrlPressed = true;
		}
		else {
			ctrlPressed = false;
		}
	}
	return password;
}

void purchaseToy() {
	vector<int> selectedToys;
	vector<int> quantities;

	int active_menu = 0;
	char ch;

	while (true) {
		int x = 50, y = 12;
		system("cls");
		cout << "Меню покупки игрушек" << endl;
		cout << "----------------------" << endl;

		for (int i = 0; i < vectToy.size(); i++) {
			if (i == active_menu) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green color
				cout << i + 1 << ". " << vectToy[i].name << " (Цена: " << vectToy[i].price << " | Количество: " << vectToy[i].quantity << ")" << endl;
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // White color
				cout << i + 1 << ". " << vectToy[i].name << " (Цена: " << vectToy[i].price << " | Количество: " << vectToy[i].quantity << ")" << endl;
			}
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectToy.size() - 1)
				++active_menu;
			break;
		case ESC:
			return;
		case ENTER:
			system("cls");
			cout << "Выбрана игрушка: " << vectToy[active_menu].name << endl;
			cout << "Текущее количество: " << vectToy[active_menu].quantity << endl;

			int quantityToBuy;
			while (true) {
				cout << "Введите количество для покупки (0 - отмена): ";
				cin >> quantityToBuy;

				if (quantityToBuy < 0) {
					cout << "Неверное значение. Количество должно быть неотрицательным." << endl;
				}
				else if (quantityToBuy > vectToy[active_menu].quantity) {
					cout << "Недостаточное количество товара. Доступное количество: " << vectToy[active_menu].quantity << endl;
				}
				else {
					break;
				}
			}

			if (quantityToBuy == 0)
				continue;

			// Добавляем выбранную игрушку и количество в соответствующие векторы
			selectedToys.push_back(active_menu);
			quantities.push_back(quantityToBuy);

			cout << "Покупка успешно добавлена." << endl;
			cout << "----------------------" << endl;
			cout << "1. Продолжить покупку" << endl;
			cout << "2. Завершить покупку" << endl;

			int choice;
			while (true) {
				cout << "Выберите действие: ";
				cin >> choice;

				if (choice == 1 || choice == 2)
					break;
				else
					cout << "Неверный выбор. Пожалуйста, повторите ввод." << endl;
			}

	
				if (choice == 2) {
					// Вывод чека
					system("cls");
					cout << "Чек" << endl;
					cout << "----------------------------------------" << endl;

					double totalCost = 0.0;

					for (int i = 0; i < selectedToys.size(); i++) {
						int toyIndex = selectedToys[i];
						int quantity = quantities[i];
						double price = vectToy[toyIndex].price;

						cout << "Игрушка: " << vectToy[toyIndex].name << endl;
						cout << "Цена за штуку: " << price << endl;
						cout << "Количество: " << quantity << endl;
						cout << "Сумма: " << price * quantity << endl;
						cout << "----------------------------------------" << endl;

						totalCost += price * quantity;
					}

					cout << "Общая стоимость: " << totalCost << endl;

					// Обновляем количество игрушек в векторе
					for (int i = 0; i < selectedToys.size(); i++) {
						int toyIndex = selectedToys[i];
						int quantity = quantities[i];

						vectToy[toyIndex].quantity -= quantity;
					}

					// Очищаем векторы выбранных игрушек и количества
					selectedToys.clear();
					quantities.clear();

					cout << "----------------------------------------" << endl;
					cout << "Спасибо за покупку!" << endl;
					cout << "Нажмите любую клавишу, чтобы продолжить...";
					_getch();

					return;
				}
				else {
					active_menu = 0;
				}

			break;
		}
	}
}

		void updateToyQuantity() {
			int y = 0;
			string* menu = new string[vectToy.size()];

			for (int i = 0; i < vectToy.size(); i++) {
				menu[i] = vectToy[i].name;
			}

			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				system("cls");
				GoToXY(x, y);
				for (int i = 0; i < vectToy.size(); i++) {
					if (i == active_menu) Green();
					else Cyan();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32) ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < vectToy.size() - 1)
						++active_menu;
					break;
				case ESC:
					delete[] menu;
					return;
				case ENTER:
					system("cls");
					GoToXY(55, 12);
					cout << "Выбрана игрушка: " << vectToy[active_menu].name << endl;
					GoToXY(55, 13);
					cout << "Текущее количество: " << vectToy[active_menu].quantity << endl;

					int newQuantity;
					while (true) {
						GoToXY(55, 14);
						cout << "Введите количество которое вы хотите добавить: ";
						cin >> newQuantity;

						if (newQuantity < 0) {
							GoToXY(55, 15);
							cout << "Неверное значение. Количество должно быть неотрицательным." << endl;
						}
						else {
							break;
						}
					}

					vectToy[active_menu].quantity += newQuantity;

					GoToXY(55, 16);
					cout << "Количество игрушки \"" << vectToy[active_menu].name << "\" изменено на: " << vectToy[active_menu].quantity << endl;
					_getch();
					delete[] menu;
					return;

				default:
					break;
				}
			}
			_getch();
			system("cls");
		}
		void AddToy() {
			Cyan();
			Toy toy;
			GoToXY(55, 12);
			getchar();
			cout << "Введите название игрушки: ";
			getline(cin, toy.name);

			GoToXY(55, 13);
			cout << "Введите цену игрушки: ";

			while (!(cin >> toy.price))
			{
				cin.clear();
				while (cin.get() != '\n'); {

					cout << "Неверный ввод. Повторите." << endl;
				}
				if (toy.price < 0) {
					cout << "Неверный ввод. Повторите." << endl;
				}
			}


			GoToXY(55, 14);
			cout << "Введите производителя игрушки: ";
			cin.ignore();
			getline(cin, toy.manufacturer);

			GoToXY(55, 15);
			cout << "Введите количество игрушек: ";
			while (!(cin >> toy.quantity))
			{
				cin.clear();
				while (cin.get() != '\n'); {

					cout << "Неверный ввод. Повторите." << endl;
				}
				if (toy.quantity < 0) {
					cout << "Неверный ввод. Повторите." << endl;
				}
			}

			GoToXY(55, 16);
			cout << "Введите минимальный возраст для игрушки: ";
			while (!(cin >> toy.minAge))
			{
				cin.clear();
				while (cin.get() != '\n'); {

					cout << "Неверный ввод. Повторите." << endl;
				}
				if (toy.minAge < 0) {
					cout << "Неверный ввод. Повторите." << endl;
				}
			}

			vectToy.push_back(toy);

			GoToXY(55, 17);
			cout << "Игрушка успешно добавлена.";
			_getch();
			system("cls");
		}

		void deleteToy() {
			int y = 0;
			string* menu = new string[vectToy.size()];

			for (int i = 0; i < vectToy.size(); i++) {
				GoToXY(55, y++);
				menu[i] = vectToy[i].name;
			}

			int active_menu = 0;
			char ch;

			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < vectToy.size(); i++) {
					if (i == active_menu)
						Green();
					else
						Cyan();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)
					ch = _getch();
				switch (ch) {
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < vectToy.size() - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:
					system("cls");
					GoToXY(55, 12);
					cout << "Игрушка " << vectToy[active_menu].name << " удалена";
					_getch();
					system("cls");
					vectToy.erase(vectToy.begin() + active_menu);
					return;
				default:
					break;
				}
			}
			_getch();
			system("cls");
		}

		void Bear() {
			Cyan();
			GoToXY(55, 9);
			cout << "Спасибо что выбрали наш магазин!";
			GoToXY(55, 11);
			std::cout << "   /\\_/\\   " << std::endl;
			GoToXY(55, 12);
			std::cout << "  ( o o )  " << std::endl;
			GoToXY(55, 13);
			std::cout << "   \\(*)/   " << std::endl;
			GoToXY(55, 14);
			std::cout << "   / ^ \\ \\  " << std::endl;
			GoToXY(55, 15);
			std::cout << "  / / \\ \\ \\  " << std::endl;
			GoToXY(55, 16);
			std::cout << "  \\ \\_/ /_/  " << std::endl;
			GoToXY(55, 17);
			std::cout << "   \\___/     " << std::endl;


			GoToXY(75, 10);
			std::cout << "     ^   ^   " << std::endl;
			GoToXY(75, 11);
			std::cout << "    / \\_/ \\  " << std::endl;
			GoToXY(75, 12);
			std::cout << "   ( о   о )  " << std::endl;
			GoToXY(75, 13);
			std::cout << "     (**)    " << std::endl;
			GoToXY(75, 14);
			std::cout << "   /         \\   __  " << std::endl;
			GoToXY(75, 15);
			std::cout << "   |         |  / /  " << std::endl;
			GoToXY(75, 16);
			std::cout << "   |         | / /     " << std::endl;
			GoToXY(75, 17);
			std::cout << "   |  |   |  |/ /     " << std::endl;
			GoToXY(75, 18);
			std::cout << "   |__|___|__|_/     " << std::endl;
			GoToXY(61, 20);
			cout << "Возвращайтесь еще)";
			cin.ignore();

		}

		void countDown(int seconds) {
			Cyan();
			int x = 55;
			GoToXY(54, 13);
			cout << "------------------------";
			GoToXY(54, 15);
			cout << "------------------------";
			GoToXY(54, 14);
			cout << "|";
			GoToXY(55, 14);
			cout << "00";
			GoToXY(77, 14);
			cout << "|";
			for (int i = seconds; i > 0; --i) {

				GoToXY(x = x + 2, 14);
				cout << "00";

				/*cout <<"Осталось: " << i <<" секунд" << endl;*/
				this_thread::sleep_for(chrono::seconds(1));

			}

		}

		void ReadUserFromFile() {
			User user;
			fstream file("users.txt", fstream::in);
			if (file.is_open()) {
				while (!file.eof()) {
					getline(file, user.login, '|');
					getline(file, user.password, '|');
					file >> user.isAdmin;
					file.ignore();
					file >> user.isBanned;
					file.ignore();
					getline(file, user.info.FIO, '|');
					file >> user.info.age;
					file.ignore();
					vectUser.push_back(user);
				}
			}
			else {
				cout << "Ошибка открытия файла\n";
			}
		}

		void Registration() {
			Cyan();
			bool isExist = false;
			int att = 0;
			User user;
			while (att != 3) {

				GoToXY(55, 12);
				cout << "Введите имя пользователя: ";
				getline(cin, user.login);
				system("cls");
				if (user.login.find(' ') != string::npos) {
					GoToXY(55, 12);
					cout << "Логин не должен содержать пробелы." << endl;
					_getch();
					system("cls");
					att++;
				}
				else {
					break;
				}
				if (att == 3) {
					GoToXY(55, 12);
					cout << "Превышено максимальное кол-во попыток, повторите еще раз через 10 секунд\n";
					countDown(10);
					att = 0;
					system("cls");
					string menu[] = { "Ввести данные заново", "Выйти" };
					int active_menu = 0;
					char ch;
					continue;
				}
			}

			for (int i = 0; i < vectUser.size(); i++) {
				if (user.login == vectUser[i].login) {
					isExist = true;
					break;
				}
			}
			if (isExist) {
				GoToXY(55, 12);
				cout << "Пользователь с таким именем уже существует";
				att++;
				_getch();
				system("cls");
			}
			else {
				int att2 = 0;
				while (att2 != 3) {
					GoToXY(55, 12);
					cout << "Введите пароль: ";
					getline(cin, user.password);
					system("cls");
					if (user.password.size() < 8) {
						GoToXY(55, 12);
						cout << "Пароль должен содержать больше 8 символов." << endl;
						att2++;
						_getch();
						system("cls");
					}
					else {
						break;
					}
					if (att2 == 3) {
						GoToXY(55, 12);
						cout << "Превышено максимальное кол-во попыток, повторите еще раз через 10 секунд\n";
						countDown(10);
						system("cls");
						att2 = 0;
						continue;
					}
				}
				setlocale(LC_ALL, "Russian");

				string FIO;
				int age;
				while (true) {
					GoToXY(55, 12);
					cout << "Введите ФИО: ";
					getline(cin, FIO);
					system("cls");
					bool hasDigits = false;
					for (char c : FIO) {
						if (isdigit(c)) {
							hasDigits = true;
							break;
						}
					}
					if (hasDigits) {
						GoToXY(55, 12);
						cout << "ФИО не должно содержать цифры." << endl;
						_getch();
						system("cls");
						continue;
					}
					else {
						user.info.FIO = FIO;
						break;
					}
				}

				while (true) {
					GoToXY(55, 12);
					cout << "Введите возраст: ";
					while (!(cin >> age))
					{
						cin.clear();
						while (cin.get() != '\n'); {

							cout << "Неверный ввод. Повторите." << endl;
						}
					}

					if (age < 0) {
						GoToXY(55, 12);
						cout << "Возраст не может быть отрицательным." << endl;
						_getch();
						system("cls");
						continue;
					}
					else {
						user.info.age = age;
						break;
					}
				}

				user.isAdmin = false;
				user.isBanned = false;
				vectUser.push_back(user);
				getchar();
			}
		}

		bool authenticateUser() {
			Cyan();
			const int MAX_ATTEMPTS = 3;
			int attempts = 0;
			bool authenticated = false;

			// Read user data from file

			string username;
			GoToXY(55, 12);
			cout << "Введите логин: ";
			getline(cin, username);
			system("cls");
			auto user = find_if(vectUser.begin(), vectUser.end(), [username](const User& u) { return u.login == username; });
			if (user == vectUser.end()) {
				GoToXY(55, 12);
				cout << "Логин неверный. Аутентификация невозможна." << endl;
				_getch();
				system("cls");
				return authenticated;
			}

			if (user->isBanned) {
				GoToXY(55, 12);
				cout << "Ваш аккаунт заблокирован." << endl;
				_getch();
				system("cls");
				return authenticated;
			}

			if (user->isAdmin) {
				while (attempts < MAX_ATTEMPTS) {
					string password;
					GoToXY(55, 12);
					cout << "Введите пароль: ";
					password = Password(password);
					system("cls");
					if (user->password == password) {
						if (user->isBanned == 0) {
							GoToXY(55, 12);
							cout << "Вы вошли как администратор." << endl;
							authenticated = true;
							_getch();
							system("cls");
							adminMenu();

							break;
						}
						else {
							GoToXY(55, 12);
							cout << "Ваш аккаунт заблокирован." << endl;
							_getch();
							system("cls");
							return authenticated;
						}
					}
					else {
						attempts++;
						GoToXY(55, 12);

						cout << "Пароль неверный. Пожалуйста, повторите попытку." << endl;
						_getch();
						system("cls");
					}
					if (attempts == MAX_ATTEMPTS) {
						GoToXY(55, 12);
						cout << "Превышено максимальное кол - во попыток,повторите еще раз через 10 секунд\n";
						countDown(10);
						attempts = 0;
						system("cls");
						continue;
					}
					return authenticated;
				}

			}

			while (attempts < MAX_ATTEMPTS) {
				string password;
				password = Password(password);

				if (user->password == password) {
					if (user->isBanned == 0) {
						GoToXY(55, 12);
						cout << "Аутентификация успешна. Вы вошли как пользователь" << endl;
						_getch();
						system("cls");
						UserMenu();

						authenticated = true;
						break;
					}
					else {
						GoToXY(55, 12);
						cout << "Ваш аккаунт заблокирован." << endl;
						return authenticated;
					}
				}
				else {
					attempts++;
					GoToXY(55, 12);
					cout << "Пароль неверный. Пожалуйста, повторите попытку." << endl;
					_getch();
					system("cls");


				}
				if (attempts == MAX_ATTEMPTS) {
					GoToXY(55, 12);
					cout << "Превышено максимальное кол - во попыток,повторите еще раз через 10 секунд\n";
					countDown(10);
					attempts = 0;
					system("cls");
					continue;
				}
			}


			return authenticated;
		}

		void banUser() {
			Cyan();
			int y = 0;
			string* menu = new string[vectUser.size()];

			for (int i = 0; i < vectUser.size(); i++) {
				GoToXY(55, y++);
				menu[i] = vectUser[i].login + ": " + vectUser[i].info.FIO;
			}

			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < vectUser.size(); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < vectUser.size() - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:
					if (vectUser[active_menu].isBanned == 0) {
						vectUser[active_menu].isBanned = 1;
						system("cls");
						GoToXY(55, 12);

						cout << "Пользователь '" << vectUser[active_menu].login << "' заблокирован";
						_getch();
						system("cls");
					}
					else {
						system("cls");
						GoToXY(55, 12);

						cout << "Пользователь '" << vectUser[active_menu].login << " 'уже заблокирован";
						_getch();
						system("cls");

					}
					return;





				default:
					break;
				}

			}

		}

		void unblockUser() {
			int y = 0;
			string* menu = new string[vectUser.size()];

			for (int i = 0; i < vectUser.size(); i++) {
				GoToXY(55, y++);
				menu[i] = vectUser[i].login + ": " + vectUser[i].info.FIO;
			}

			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < vectUser.size(); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < vectUser.size() - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:
					if (vectUser[active_menu].isBanned == 1) {
						vectUser[active_menu].isBanned = 0;
						system("cls");
						GoToXY(55, 12);
						cout << "Пользователь '" << vectUser[active_menu].login << "' разблокирован";
						_getch();
						system("cls");
					}
					else {
						system("cls");
						GoToXY(55, 12);
						cout << "Пользователь '" << vectUser[active_menu].login << "' уже разблокирован";
						_getch();
						system("cls");

					}
					return;





				default:
					break;
				}

			}
		}





		void deleteUser() {
			int y = 0;
			string* menu = new string[vectUser.size()];

			for (int i = 0; i < vectUser.size(); i++) {
				GoToXY(55, y++);
				menu[i] = vectUser[i].login + ": " + vectUser[i].info.FIO;
			}

			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < vectUser.size(); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < vectUser.size() - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:
					system("cls");
					GoToXY(55, 12);
					cout << "Пользователь " << vectUser[active_menu].login << "' удален";
					_getch();
					system("cls");
					vectUser.erase(vectUser.begin() + active_menu);
					return;





				default:
					break;
				}

			}

		}

		void OverwriteUser() {

			fstream inf;

			inf.open("users.txt", fstream::out);
			for (int i = 0; i < vectUser.size(); i++) {
				inf << vectUser[i].login << "|" << vectUser[i].password << "|" <<
					vectUser[i].isAdmin << "|" << vectUser[i].isBanned << "|" <<
					vectUser[i].info.FIO << "|" << vectUser[i].info.age;
				if (i != vectUser.size() - 1) {
					inf << endl;
				}
			}
			inf.close();
		}


		void ReadToysFromFile() {
			Toy toys;
			fstream infile("toys.txt", fstream::in);
			if (infile.is_open()) {
				while (!infile.eof()) {
					getline(infile, toys.name, '|');
					infile >> toys.price;
					infile.ignore();
					getline(infile, toys.manufacturer, '|');
					infile >> toys.quantity;
					infile.ignore();
					infile >> toys.minAge;
					infile.ignore();

					vectToy.push_back(toys);
				}
			}
			else {
				cout << "Ошибка открытия файла\n";
			}
		}

		void OverwriteToys() {

			fstream inf;

			inf.open("toys.txt", fstream::out);
			for (int i = 0; i < vectToy.size(); i++) {

				inf << vectToy[i].name << '|'
					<< vectToy[i].price << '|'
					<< vectToy[i].manufacturer << '|'
					<< vectToy[i].quantity << '|'
					<< vectToy[i].minAge;
				if (i != vectToy.size() - 1) {
					inf << endl;
				}

			}
			inf.close();
		}

		void DisplayToys() {
			Cyan();

			cout << left << setw(40) << "Название" << '|'
				<< setw(10) << "Цена" << '|'
				<< setw(15) << "Производитель" << '|'
				<< setw(10) << "Количество" << '|'
				<< setw(19) << "Минимальный возраст" << '|' << endl;

			cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
			for (int i = 0; i < vectToy.size(); i++) {

				cout << left << setw(40) << vectToy[i].name << '|'
					<< setw(10) << vectToy[i].price << '|'
					<< setw(15) << vectToy[i].manufacturer << '|'
					<< setw(10) << vectToy[i].quantity << '|'
					<< setw(19) << vectToy[i].minAge << '|' << endl;

				cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
			}
		}
		void AdminDisplayToys() {
			Cyan();

			cout << left << setw(40) << "Название" << '|'
				<< setw(10) << "Цена" << '|'
				<< setw(15) << "Производитель" << '|'
				<< setw(10) << "Количество" << '|'
				<< setw(19) << "Минимальный возраст" << '|' << endl;

			cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
			for (int i = 0; i < vectToy.size(); i++) {
				if (vectToy[i].quantity < 3) {
					cout << "\033[31m";  // Set text color to red
				}

				cout << left << setw(40) << vectToy[i].name << '|'
					<< setw(10) << vectToy[i].price << '|'
					<< setw(15) << vectToy[i].manufacturer << '|'
					<< setw(10) << vectToy[i].quantity << '|'
					<< setw(19) << vectToy[i].minAge << '|' << endl;

				if (vectToy[i].quantity < 3) {
					Cyan();
				}

				cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
			}
			_getch();
			system("cls");
		}

		void sortToysByName() {
			for (int i = 0; i < vectToy.size() - 1; i++) {
				for (int j = i + 1; j < vectToy.size(); j++) {
					if (vectToy[i].name > vectToy[j].name) {
						swap(vectToy[i], vectToy[j]);
					}
				}
			}
		}

		void sortByPrice() {
			for (int i = 0; i < vectToy.size() - 1; i++) {
				for (int j = 0; j < vectToy.size() - i - 1; j++) {
					if (vectToy[j].price > vectToy[j + 1].price) {
						Toy temp = vectToy[j];
						vectToy[j] = vectToy[j + 1];
						vectToy[j + 1] = temp;
					}
				}
			}
		}
		void sortByQuantity() {
			for (int i = 0; i < vectToy.size() - 1; i++) {
				for (int j = 0; j < vectToy.size() - i - 1; j++) {
					if (vectToy[j].quantity > vectToy[j + 1].quantity) {
						swap(vectToy[j], vectToy[j + 1]);
					}
				}
			}
		}


		void searchByName()
		{
			Cyan();
			string searchName;
			bool found = false;
			GoToXY(55, 12);
			cout << "Введите название игрушки, которую желаете найти: ";

			while (true) {
				char ch = _getch();
				if (ch == '\r') {  // Enter key
					break;
				}
				if (ch == '\b') {  // Backspace key
					if (!searchName.empty()) {
						searchName.pop_back();
						system("cls");
					}
					continue;
				}
				searchName += tolower(ch);
				system("cls");
				found = false;
				cout << "Введите название игрушки, которую желаете найти: " << searchName;
				for (int i = 0; i < vectToy.size(); i++) {
					string toyName = vectToy[i].name;
					string lowerToyName;
					for (char& c : toyName) {
						c = tolower(c);
					}
					if (toyName.find(searchName) == 0) {
						if (!found) {
							cout << "\n" << left << setw(40) << "Название" << '|'
								<< setw(10) << "Цена" << '|'
								<< setw(15) << "Производитель" << '|'
								<< setw(10) << "Количество" << '|'
								<< setw(19) << "Минимальный возраст" << '|' << endl;
							cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
							found = true;
						}
						cout << left << setw(40) << vectToy[i].name << '|'
							<< setw(10) << vectToy[i].price << '|'
							<< setw(15) << vectToy[i].manufacturer << '|'
							<< setw(10) << vectToy[i].quantity << '|'
							<< setw(19) << vectToy[i].minAge << '|' << endl;
						cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
					}
				}
				if (!found) {
					GoToXY(55, 12);
					cout << "Игрушка с таким именем не найдена." << endl;
				}
			}


			if (searchName.empty()) {  // Show all toys if searchName is empty
				found = true;
				for (int i = 0; i < vectToy.size(); i++) {
					if (!found) {
						cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
					}
					cout << left << setw(40) << vectToy[i].name << '|'
						<< setw(10) << vectToy[i].price << '|'	
						<< setw(15) << vectToy[i].manufacturer << '|'
						<< setw(10) << vectToy[i].quantity << '|'
						<< setw(19) << vectToy[i].minAge << '|' << endl;
					cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
					found = true;
				}
			}


			if (!found) {
				GoToXY(55, 12);
				cout << "Игрушка с таким именем не найдена." << endl;
			}

		}



		void searchToysByAge() {
			Cyan();
			int age;
			GoToXY(55, 12);

			cout << "Введите возраст для поиска игрушек: ";
			cin >> age;
			system("cls");
			bool found = false;
			for (int i = 0; i < vectToy.size(); i++) {
				if (vectToy[i].minAge <= age) {
					if (!found) {
						cout << left << setw(40) << "Название" << '|'
							<< setw(10) << "Цена" << '|'
							<< setw(15) << "Производитель" << '|'
							<< setw(10) << "Количество" << '|'
							<< setw(19) << "Минимальный возраст" << '|' << endl;
						cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
						found = true;
					}
					cout << left << setw(40) << vectToy[i].name << '|'
						<< setw(10) << vectToy[i].price << '|'
						<< setw(15) << vectToy[i].manufacturer << '|'
						<< setw(10) << vectToy[i].quantity << '|'
						<< setw(19) << vectToy[i].minAge << '|' << endl;
					cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
				}
			}
			if (!found) {
				GoToXY(55, 12);

				cout << "Игрушки для данного возраста не найдены." << endl;
				_getch();
				system("cls");
			}
		}

		void filterToysByPrice() {
			Cyan();
			double min_price, max_price;
			GoToXY(55, 12);

			cout << "Введите минимальную цену: ";
			cin >> min_price;
			GoToXY(55, 13);

			cout << "Введите максимальную цену: ";
			cin >> max_price;
			system("cls");
			cout << left << setw(40) << "Название" << '|'
				<< setw(10) << "Цена" << '|'
				<< setw(15) << "Производитель" << '|'
				<< setw(10) << "Количество" << '|'
				<< setw(19) << "Минимальный возраст" << '|' << endl;
			cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;

			for (int i = 0; i < vectToy.size(); i++) {
				if (vectToy[i].price >= min_price && vectToy[i].price <= max_price) {
					cout << left << setw(40) << vectToy[i].name << '|'
						<< setw(10) << vectToy[i].price << '|'
						<< setw(15) << vectToy[i].manufacturer << '|'
						<< setw(10) << vectToy[i].quantity << '|'
						<< setw(19) << vectToy[i].minAge << '|' << endl;
					cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
				}
			}

		}

		void filterToysByQuantity() {
			Cyan();
			int min_quantity, max_quantity;
			GoToXY(55, 12);

			cout << "Введите минимальное количество: ";
			cin >> min_quantity;
			GoToXY(55, 13);

			cout << "Введите максимальное количество: ";
			cin >> max_quantity;
			system("cls");
			cout << left << setw(40) << "Название" << '|'
				<< setw(10) << "Цена" << '|'
				<< setw(15) << "Производитель" << '|'
				<< setw(10) << "Количество" << '|'
				<< setw(19) << "Минимальный возраст" << '|' << endl;
			cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;

			for (int i = 0; i < vectToy.size(); i++) {
				if (vectToy[i].quantity >= min_quantity && vectToy[i].quantity <= max_quantity) {
					cout << left << setw(40) << vectToy[i].name << '|'
						<< setw(10) << vectToy[i].price << '|'
						<< setw(15) << vectToy[i].manufacturer << '|'
						<< setw(10) << vectToy[i].quantity << '|'
						<< setw(19) << vectToy[i].minAge << '|' << endl;
					cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;
				}
			}
		}


		void mainMenu() {
			Cyan();
			GoToXY(55, 12);
			cout << "ДОБРОГО ВРЕМЕНИ СУТОК!!";
			GoToXY(50, 13);
			cout << "Вас приветствует магазин игрушек.";
			GoToXY(50, 14);
			cout << "Чтобы продолжить работу вам необходимо войти в аккаунт";
			GoToXY(50, 15);
			cout << "или зарегистрировать новый аккаунт.";
			_getch();
			system("cls");
			int y = 0;
			string menu[] = { "Зарегистрироваться","Авторизация","Просмотреть каталог игрушек","Завершить программу" };



			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < size(menu); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < size(menu) - 1)
						++active_menu;
					break;

				case ENTER:

					switch (active_menu)
					{
					case 0:
						system("cls");

						Registration();
						_getch();
						system("cls");
						break;
					case 1:
						system("cls");

						authenticateUser();

						break;
					case 2:
						system("cls");

						DisplayToys();
						_getch();
						system("cls");
						break;
					case 3:
						system("cls");
						Bear();
						OverwriteUser();
						OverwriteToys();
						exit(0);
					}





				default:
					break;
				}
			}

		}
		void sortMenu() {
			int y = 0;
			string menu[] = { "Сортировать игрушки по имени","Сортировать игрушки по цене","Сортировать игрушки по кол-ву","Назад" };



			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < size(menu); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < size(menu) - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:

					switch (active_menu)
					{
					case 0:
						system("cls");

						sortToysByName();
						DisplayToys();
						_getch();
						system("cls");
						break;
					case 1:
						system("cls");

						sortByPrice();
						DisplayToys();
						_getch();
						system("cls");
						break;
					case 2:
						system("cls");

						sortByQuantity();
						DisplayToys();
						_getch();
						system("cls");
						break;

					case 3:
						system("cls");
						UserMenu();
					}





				default:
					break;
				}
			}
		}

		void filtrMenu() {
			int y = 0;
			string menu[] = { "Найти игрушки по имени","Фильтровать игрушки по ценовому промежутку","Фильтровать игрушки по количеству","Фильтровать игрушки по возоасту","Назад" };



			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < size(menu); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < size(menu) - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:

					switch (active_menu)
					{
					case 0:
						system("cls");

						searchByName();
						_getch();
						system("cls");
						break;
					case 1:
						system("cls");

						filterToysByPrice();
						_getch();
						system("cls");
						break;
					case 2:
						system("cls");

						filterToysByQuantity();
						_getch();
						system("cls");
						break;
					case 3:
						system("cls");
						searchToysByAge();
						_getch();
						system("cls");

					case 4:
						system("cls");
						UserMenu();
					}





				default:
					break;
				}
			}
		}
		void adminMenu() {
			int y = 0;
			string menu[] = { "Заблокировать пользователя","Разблокировать пользователя","Удалить пользователя","Добавить новую игрушку","Удалить игрушку","Просмотреть каталог игрушек","Добавить существующую игрушку","Выйти из аккаунта" };



			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < size(menu); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < size(menu) - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:

					switch (active_menu)
					{
					case 0:
						system("cls");

						banUser();

						break;
					case 1:
						system("cls");

						unblockUser();

						break;
					case 2:
						system("cls");

						deleteUser();

						break;
					case 3:
						system("cls");
						AddToy();
						break;
					case 4:

						system("cls");
						deleteToy();
						break;
					case 5:
						system("cls");
						AdminDisplayToys();
						break;

					case 6:
						system("cls");
						updateToyQuantity();
						system("cls");
						break;

					case 7:
						system("cls");
						mainMenu();
					}





				default:
					break;
				}
			}
		}

		void UserMenu() {
			int y = 0;
			string menu[] = { "Просмотреть каталог игрушек","Отсортировать игрушки по какому-либо параметру","Отфильтровать игрушки по какому-либо параметру","Совершить покупку","Выйти из аккаунта" };



			int active_menu = 0; char ch;
			while (true) {
				int x = 50, y = 12;
				GoToXY(x, y);
				for (int i = 0; i < size(menu); i++) {
					if (i == active_menu)Green();
					else Purpule();
					GoToXY(x, y++);
					cout << menu[i] << endl;
				}
				ch = _getch();
				if (ch == -32)ch = _getch();
				switch (ch)
				{
				case UP:
					if (active_menu > 0)
						--active_menu;
					break;
				case DOWN:
					if (active_menu < size(menu) - 1)
						++active_menu;
					break;
				case ESC:
					exit(0);
				case ENTER:

					switch (active_menu)
					{
					case 0:
						system("cls");

						DisplayToys();
						_getch();
						system("cls");
						break;
					case 1:
						system("cls");

						sortMenu();
						_getch();
						system("cls");
						break;
					case 2:
						system("cls");

						filtrMenu();
						_getch();
						system("cls");
						break;
					case 3:
						system("cls");
						purchaseToy();
						system("cls");
						break;
					case 4:
						system("cls");
						mainMenu();
					}





				default:
					break;
				}
			}

		}
		




		void main() {
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			ReadUserFromFile();
			ReadToysFromFile();
			mainMenu();


		}
