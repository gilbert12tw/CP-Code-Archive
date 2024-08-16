import os

def search_word_in_file(filepath, word):
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as file:
        for line in file:
            if word in line:
                return True
    return False

def search_word_in_directory(directory, word):
    cpp_files_with_word = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp'):
                filepath = os.path.join(root, file)
                if search_word_in_file(filepath, word):
                    cpp_files_with_word.append(filepath)
    return cpp_files_with_word

# Get the directory and search word from the user
directory_path = input("Enter the path to the directory: ")
search_word = input("Enter the word to search for: ")

# Find all .cpp files containing the word
files_with_word = search_word_in_directory(directory_path, search_word)

# Print the results
if files_with_word:
    print(f"The word '{search_word}' was found in the following .cpp files:")
    for file in files_with_word:
        print(file)
else:
    print(f"No .cpp files containing the word '{search_word}' were found in the directory.")

