PROJEKT JPO - ASYSTENT IT (AdminAssistant)


OPIS:
Aplikacja w języku C++ z interfejsem graficznym (Qt), służąca do automatyzacji pracy administratora IT. 
Wykorzystuje lokalny model językowy (Ollama) do tłumaczenia poleceń użytkownika na komendy systemowe Windows (CMD), 
wykonywania ich w tle za pomocą QProcess (podejście wielowątkowe), a następnie analizowania surowych wyników 
z konsoli i generowania raportów.

INSTRUKCJA URUCHOMIENIA:
1. Upewnij się, że w tle uruchomiony jest program Ollama wraz z pobranym modelem qwen2.5:3b.
2. Otwórz projekt (AdminAssistant.pro / CMakeLists.txt) w środowisku Qt Creator.
3. Skompiluj projekt używając zestawu narzędzi MinGW 64-bit lub MSVC.
4. Uruchom aplikację. Wpisz cel (np. 8.8.8.8) i zadanie (np. napisz maila o statusie), a następnie kliknij przycisk.

INSTRUKCJA URUCHOMIENIA TESTÓW:
1. W środowisku Qt Creator otwórz dolny panel "Test Results" (Wyniki testów) lub wciśnij Alt + 8.
2. Kliknij zielony trójkąt "Run All Tests", aby skompilować i uruchomić aplikację testową (AppTests).
3. Środowisko automatycznie zweryfikuje poprawność logiki walidacji oraz parsowania formatu JSON.