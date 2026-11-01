import subprocess
import sys

# Lista de testes corrigida
tests = [
    # Chars
    ("a", ["char: 'a'", "int: 97", "float: 97.0f", "double: 97.0"]),
    ("*", ["char: '*'", "int: 42", "float: 42.0f", "double: 42.0"]),
    
    # Ints / Números
    ("0", ["char: Non displayable", "int: 0", "float: 0.0f", "double: 0.0"]),
    ("42", ["char: '*'", "int: 42", "float: 42.0f", "double: 42.0"]), 
    ("-42", ["char: impossible", "int: -42", "float: -42.0f", "double: -42.0"]),
    ("2147483647", ["int: 2147483647"]),
    ("-2147483648", ["int: -2147483648"]),
    
    # Floats & Doubles
    ("0.0f", ["float: 0.0f", "double: 0.0"]),
    ("42.0f", ["float: 42.0f", "double: 42.0"]),
    ("42.42f", ["float: 42.4f", "double: 42.4"]),
    ("42.42", ["float: 42.4f", "double: 42.4"]),
    ("42f", ["char: '*'", "int: 42", "float: 42.0f", "double: 42.0"]), # 42f é um float válido
    ("42.99999999999999", ["char: '*'", "int: 42", "float: 42.0f", "double: 42.0"]), # 42f é um float válido
        
    # Pseudo-literals
    ("nan", ["char: impossible", "int: impossible", "float: nanf", "double: nan"]),
    ("nanf", ["char: impossible", "int: impossible", "float: nanf", "double: nan"]),
    ("+inf", ["char: impossible", "int: impossible", "float: inff", "double: inf"]),
    ("-inf", ["char: impossible", "int: impossible", "float: -inff", "double: -inf"]),
    ("-inff", ["char: impossible", "int: impossible", "float: -inff", "double: -inf"]),
    
    # Inválidos / Erros
    ("", ["char: impossible", "int: impossible", "float: impossible", "double: impossible"]),
    ("hello", ["char: impossible", "int: impossible", "float: impossible", "double: impossible"]),
    ("42.42.42", ["char: impossible", "int: impossible", "float: impossible", "double: impossible"]),
]

def run_tests():
    print("Compilando o projeto com 'make'...")
    compile_process = subprocess.run(["make"], capture_output=True, text=True)
    if compile_process.returncode != 0:
        print("Erro de compilação:")
        print(compile_process.stderr)
        sys.exit(1)
    print("Compilação bem-sucedida!\n" + "="*40)

    passed = 0
    failed = 0

    for i, (arg, expected_substrings) in enumerate(tests):
        process = subprocess.run(["./ScalarConverter", arg], capture_output=True, text=True)
        output = process.stdout

        all_found = True
        missing = []
        for sub in expected_substrings:
            if sub not in output:
                all_found = False
                missing.append(sub)

        print(f"Teste {i+1:02d} | Input: '{arg}'", end=" -> ")
        if all_found:
            print("\033[92mPASSOU\033[0m")
            passed += 1
        else:
            print("\033[91mFALHOU\033[0m")
            print(f"  Esperava encontrar: {expected_substrings}")
            print(f"  Output obtido:\n{output.strip()}")
            failed += 1

    print("="*40)
    print(f"Resultados: {passed} passaram, {failed} falharam.")

if __name__ == "__main__":
    run_tests()
