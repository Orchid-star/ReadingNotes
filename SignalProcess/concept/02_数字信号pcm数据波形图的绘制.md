```matlab
% step1: 采样设置
fs = 44100;				% 采样率, 点数/s
duration = 1 * 10;		% 信号持续时间，s
t = linspace(0, duration, fs * duration);	%数字信号采样点时刻

% step2: 模拟信号 sin(2*pi*f1*t) + sin(2*pi*f2*t) 
f1 = 440;
f2 = 880;

% step3: 采样
signal = sin(2*pi*f1*t) + sin(2*pi*f2*t);

% step4: 量化
bits = 16;
amplitude = 3;		%量化单位：2*amplitude/2^bits
pcm = round(signal/(2*amplitude/2^bits));

% step5: 编码保存
% filename = 'ret/ad_trans.pcm';
% fid = fopen(filename,'w');
% fwrite(fid, pcm, 'int16');
% fclose(fid);

% 绘制波形图
y = pcm / (2^(bits-1));
plot(t, y);
```



**量化单位**

量化时，振幅的量化范围是振幅最大值的两倍，所以是2 * amplitude / 2^bits，考虑单边，则是amplitude / 2^(bits-1)

绘制波形时，进行归一化操作，所以对pcm的每个数据除以其上限的绝对值，所以是pcm/2^(bits-1)。

audition的波形图纵坐标是dB，只不过是显示纵轴时，对刻度进行了20log~10~(标签)的显示处理。