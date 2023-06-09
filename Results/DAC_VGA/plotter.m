clc;
clear

dataraw = readmatrix("200kHz_0_02V_1M_SPI_PIO_RAMP.csv").';
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
plot(data)
%%
figure;
hold on;


% Define the desired y-axis limits
yMin = -0.3;
yMax = 0.3;

% Define the number of tick values you want
numTicks = 11; % Adjust this value as needed

% Calculate the tick values
tickValues = linspace(yMin, yMax, numTicks);

% Specify the number of decimal places
decimalPlaces = 3; % Adjust this value as needed

% Format the tick labels with the desired precision
tickLabels = sprintf(['%.' num2str(decimalPlaces) 'f\n'], tickValues);

% Calculate the time values for the x-axis
sampleRate = 1; % Sample rate in samples per second
numSamples = 151; % Number of samples
time = (0:numSamples-1) / sampleRate;

data = data(930:1080);
plot(time,data-1.5);

% Define the desired x-axis limits
xMin = min(time);
xMax = max(time);

% Define the number of tick values you want
numXTicks = 6; % Adjust this value as needed

% Calculate the tick values
xTickValues = linspace(xMin, xMax, numXTicks);

% Set the x-axis tick properties
xticks(xTickValues);

 %Set the y-axis limits and tick properties
ylim([yMin yMax]);
yticks(tickValues);
yticklabels(tickLabels);
xlabel('Time (\mu s)');
ylabel('Amplitude (V)');
title('Gain Ramp of MCP4921 DAC sampled at 1Msps (Using PIO SPI)')
grid on
