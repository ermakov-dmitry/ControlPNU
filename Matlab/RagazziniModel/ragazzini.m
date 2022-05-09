clc;
close all;
% clear all variables;

k = 1;
k1 = 0.5;
k2 = 0.1;
k3 = 0.5;
tau = 0.5;

t = out.yout{1}.Values.Time;
y = out.yout{1}.Values.Data;
u = out.yout{2}.Values.Data;

figure;
clf;
plot(t, u, t, y);
legend({'u(t)', 'y(t)'}, 'interpreter', 'latex')
grid on;
matlab2tikz('rag_step.tex')