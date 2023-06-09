clc;
clear

dataraw = readmatrix("5M_0_02V_41M.csv").';
data = dataraw(1,:);
%data2 = dataraw(28,:);
%data3 = dataraw(29,:);
x = 0.684;
%data = (data>=x/2).*data;
%(data>x/2).*(data-x)+

%for i = 1:500
    %if data(i) > x/2
        %data(i) = data(i) - x;
    %end
%end


figure;
hold on;
%plot(data(100:140));

% plot(data3(1:100));

% Define the desired y-axis limits
yMin = -0.6;
yMax = 0.6;

% Define the number of tick values you want
numTicks = 11; % Adjust this value as needed

% Calculate the tick values
tickValues = linspace(yMin, yMax, numTicks);

% Specify the number of decimal places
decimalPlaces = 3; % Adjust this value as needed

% Format the tick labels with the desired precision
tickLabels = sprintf(['%.' num2str(decimalPlaces) 'f\n'], tickValues);

% Calculate the time values for the x-axis
sampleRate = 41; % Sample rate in samples per second
numSamples = 40; % Number of samples
time = (0:numSamples-1) / sampleRate;
plot(time,(data(3:42)-1.25)*1.5,'LineWidth',1);

% Set the y-axis limits and tick properties
ylim([yMin yMax]);
yticks(tickValues);
yticklabels(tickLabels);
xlabel('Time (\mu s)');
ylabel('Amplitude (mV)');
title('5MHz Sine Wave Sampled at 41Msps using LTC2236')
grid on


