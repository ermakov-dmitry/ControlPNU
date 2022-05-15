clc;
close all;
clear variables;

%% Init
f = {'0.1'; '0.2'; '0.3'; '0.4'; '0.5'; '0.6'; '0.7';...
    '0.8'; '0.9'; '1.0'; '1.1'; '1.3'; '1.5'; '1.7'; '1.9'};
amplitude = {'5'; '10'; '20'; '30'; '45'; '60'};

y_signal = {};  % {f, amplitude} -> [signal, time]
u_signal = {};
data.signal = [];
data.time = [];
lachx = zeros(length(f), length(amplitude), 2);
n_periods = 1;  % number of periods cut from signal and time (max 19) 

%% Read and calc data
for i = 1:length(f)
    for j = 1:length(amplitude)
        filename_input = strcat('freqlog_el/input_freq_',...
            f{i, 1}, '_amplitude_', amplitude{j, 1}, '.csv');
        filename_output = strcat('freqlog_el/output_freq_',...
            f{i, 1}, '_amplitude_', amplitude{j, 1}, '.csv');
        T_in = readtable(filename_input, 'NumHeaderLines', 1);
        T_out = readtable(filename_output, 'NumHeaderLines', 1);
        u_signal{i, j} = cut_n_periods(T_in.Var2,...
            T_in.Var3, str2double(f{i, 1}), n_periods); 
        y_signal{i, j} = cut_n_periods(T_out.Var2,...
            T_out.Var3, str2double(f{i, 1}), n_periods);

        % calc freqs
        d_time = mean(((y_signal{i, j}(:, 2)) - y_signal{i, j}(1, 2))...
            / length(y_signal{i, j}(:, 2))) * 2;
        lachx(i, j, :) = calc_laphcx(y_signal{i, j}(:, 1),...
            u_signal{i, j}(:, 1),...
        str2double(amplitude{j, 1}), str2double(f{i, 1}), d_time);
    end
end
%lachx(9, 6, 1) = lachx(8, 6, 1) / 2 + lachx(10, 6, 1) / 2;  % fix anomaly

%% Ploting results
f_num = cell2mat([cellfun(@str2double, f, 'un', 0).'])';

% plot response
figure;
clf;
subplot(2, 2, 1);
plot(u_signal{1, 1}(:, 2), u_signal{1, 1}(:, 1));
hold on;
plot(y_signal{1, 1}(:, 2), y_signal{1, 1}(:, 1), '--');
hold off;
title('u(t) = 5sin(0.2\pit)');
grid on;
legend({'u(t)', 'y(t)'})

subplot(2, 2, 2);
plot(u_signal{6, 3}(:, 2), u_signal{6, 3}(:, 1));
hold on;
plot(y_signal{6, 3}(:, 2), y_signal{6, 3}(:, 1), '--');
hold off;
title('u(t) = 20sin(1.2\pit)');
grid on;
legend({'u(t)', 'y(t)'})

subplot(2, 2, 3);
plot(u_signal{8, 4}(:, 2), u_signal{8, 4}(:, 1));
hold on;
plot(y_signal{8, 4}(:, 2), y_signal{8, 4}(:, 1), '--');
hold off;
title('u(t) = 45sin(1.6\pit)');
grid on;
legend({'u(t)', 'y(t)'})

subplot(2, 2, 4);
plot(u_signal{12, 6}(:, 2), u_signal{12, 6}(:, 1));
hold on;
plot(y_signal{12, 6}(:, 2), y_signal{12, 6}(:, 1), '--');
hold off;
title('u(t) = 60sin(2.6\pit)');
grid on;
legend({'u(t)', 'y(t)'})
% matlab2tikz('response.tex');


% plot bode
w = f_num * 2 * pi;
L_i = 20 * log10(1 ./ w);
line = [-10 10];
figure('Name', 'All Lachx');
clf;
semilogx(w, lachx(:, 1, 1), w, lachx(:, 2, 1), w, lachx(:, 3, 1),...
    w, lachx(:, 4, 1), w, lachx(:, 5, 1), w, lachx(:, 6, 1));
hold on;
semilogx(w, L_i, '--');
hold on;
semilogx([w(2) w(2)] , line, '--');
text(w(2) + 0.01, 1, strcat('\leftarrow \omega = ', num2str(w(2)),...
    ' rad/s', ', f = ', num2str(w(2) / 2 / pi), ' Hz'));
hold off;
grid on;
xlabel('\omega, rad/s');
ylabel('L(\omega)');
legend({amplitude{1, 1}, amplitude{2, 1}, amplitude{3, 1},...
    amplitude{4, 1}, amplitude{5, 1}, amplitude{6, 1}, '1/s'},...
    'Location', 'southwest');
matlab2tikz('lachx_el.tex');
