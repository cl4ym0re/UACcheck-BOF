<h1>checkUAC-BOF</h1>

一个通过读取ConsentPromptBehaviorAdmin的值并用于判断当前主机UAC等级的BOF，主要为了实现bypassUAC的前期探测工作。  （钓鱼上来的机器如果uac等级为Always Notify的话，bypassuac会直接弹框，动静很大）<br><br>
A BOF that you should execute before you bypassUAC.

<h2>如图：</h2>

<img src="https://github.com/cl4ym0re/checkUAC-BOF/blob/main/always.png?raw=true" alt="image" />
碰到这种环境，谨慎对待你的beacon

 <h2>感谢：</h2>

https://github.com/securifybv/Visual-Studio-BOF-template






