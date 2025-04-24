# 🐚 Minishell - A Simple UNIX Shell Implementation  

**42 Firenze Project | Systems Programming**  
*Shell personalizzata con supporto a pipe, redirezioni, variabili d'ambiente e built-in commands*  

---

## 📜 Cosa Richiede il Progetto (Mandatory Part)  

### 🎯 Obiettivi Principali  
- Creare un **sostituto interattivo di bash** con:  
  - Prompt personalizzato  
  - History dei comandi  
  - Espansione variabili (`$VAR`, `$?`)  

### ⚙️ Funzionalità Implementate  
- **Gestione Input**:  
  - Quote handling (`'` e `"`)  
  - Segnali (`ctrl-C`, `ctrl-D`, `ctrl-\`)  
- **Esecuzione Comandi**:  
  - PATH resolution (`/bin/ls` o `ls`)  
  - Built-in:  
    ```bash
    echo, cd, pwd, export, unset, env, exit
    ```  
- **Advanced Features**:  
  - Pipe (`|`)  
  - Redirezioni (`>`, `>>`, `<`, `<<`)  

---

## 🛠️ Installazione & Utilizzo  
```bash
git clone https://github.com/mttgvnrd/minishell.git
cd minishell
make  # Compila il progetto

# Esegui
./minishell
