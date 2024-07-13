# redteam

## source-codes
*reverse-shell-hollowing.cs* - This C# code executes a reverse shell using the Process Hollowing technique, where a victim process is created in a suspended state, its original process (e.g.: notepad.exe) is carved out from memory, a malicious binary gets written instead and the program state is resumed to execute the injected code.
You can compile it with mcs hollowing.cs
