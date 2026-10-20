%% Paramètres signal d'entrée (BBGC)
N = 2000;
moyenne = 0;
variance = 0.5;
b = moyenne + sqrt(variance) * randn(1, N);
t = 0:N-1;


%% Configuration du filtre 1 (MA d'ordre 4)
%-----------------------------------------

A =0.95;                                %module des zeros
fn_rej = [-4/9 -1/4 1/4 4/9];           %fréquences normalisées des réjections
arguments = 2*pi*fn_rej;                %arguments des zeros
Z = A*exp(j*arguments);                 %les zeros de H1

H1= poly(Z);                            % Coefficients du polynôme dont les racines sont les zéros du filtre.
subplot(2,1,1)
zplane(H1)                              %on trace les zeros
axis equal;
title('Les Zéros de H_1')
xlabel('Partie réelle');
ylabel('Partie imaginaire');

%% le signal à la sortie
x=filter(H1,1,b); 

X=fftshift(fft(x));
subplot(2,1,2)
plot(t,x)
title('signal de sortie du MA (x[k])')


%% Comparaison des estimations de DSP en sortie du filtre MA
ComparateurSpectres(x, H1, 1, variance, fn_rej, 'MA')
% (5 figures)

%% Configuration du filtre 2 (AR d'ordre 4)
%-----------------------------------------

A=0.99;                                 %module des pôles
fn_res = [-3/7 -1/3 1/3 3/7];           %fréquences normalisées des réjections
arguments = 2*pi*fn_res;                %arguments des pôles
P = A*exp(j*arguments);                 %les pôles de H2

Q= poly(P);                             % Coefficients du polynôme dont les racines sont les pôles du filtre.
figure;
subplot(2,1,1)
zplane(1,Q)                             %on trace les pôles
axis equal;
title('Les pôles de H_2')
xlabel('Partie réelle');
ylabel('Partie imaginaire');

%% le signal à la sortie
y=filter(1,Q,b); 

Y=fftshift(fft(y));
subplot(2,1,2)
plot(t,y)
title('signal de sortie du AR (y[k])')


%% Comparaison des estimations de DSP en sortie du filtre AR
ComparateurSpectres(y, 1, Q, variance, fn_res, 'AR')
% (5 figures)