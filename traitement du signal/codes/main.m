%% Paramètres signal d'entrée (BBGC)
N = 2000;
moyenne = 0;
variance = 0.5;
b = moyenne + sqrt(variance) * randn(1, N);
t = 0:N-1;


figure;
subplot(3,1,1)
plot(t,b)
title('le bruit blanc gaussien')

%% Configuration du filtre 2 (AR d'ordre 4)
A=0.99; %module des pôles
fn_res = [-3/7 -1/3 1/3 3/7]; %fréquences normalisées des réjections
arguments = 2*pi*fn_res; %arguments des pôles
P = A*exp(j*arguments); %les pôles de H2

Q= poly(P);
subplot(3,1,2)
zplane(1,Q) %on trace les pôles
title('Les pôles de H_2')
xlabel('Partie réelle');
ylabel('Partie imaginaire');


fn= linspace(-1/2,1/2 - 1/N,N); %inclut -0.5 mais pas 0.5
%% le signal à la sortie
y=filter(1,Q,b); 

Y=fftshift(fft(y));
subplot(3,1,3)
plot(t,y)
title('signal de sortie du AR (y[k])')

%% Périodogramme brut
dsp_pratique= (abs(Y).^2)/N;


%% DSP théorique
h2= freqz(1, Q, 2*pi*fn);
dsp_theorique= variance* (abs(h2).^2);

%% Périodogramme de Daniell (1 paramètre)
M=100;
dsp_daniell = dspdaniell(dsp_pratique, 100);


%% Périodogramme de Bartlett (1 paramètre)
L=1000; %longueur des segments
dsp_bartlett= dspbartlett(y,L,N);
fn_bartlett= linspace(-1/2,1/2 - 1/L,L);

%% Périodogramme de Welch (2 paramètres)
L_welch=80; %longueur des segments
R=70; %recouvrement
dsp_welch = dspwelch(fn, y,L_welch, R);

%% Corrélogramme (1 paramètre)
K = 250;                                        % nombre de retards, K << N (et N > 2K)
[Ryy, ~] = xcorr(y - mean(y), K, 'biased');     % retards -K..K, longueur 2K+1
Rw = Ryy(:) .* bartlett(2*K+1);                 % pondération de Bartlett

r = zeros(N,1);
r(1:K+1)   = Rw(K+1:end);                       % retards 0..K
r(N-K+1:N) = Rw(1:K);                           % retards -K..-1
dsp_correlo = fftshift(real(fft(r)));

figure;
plot(fn, 10*log10(max(dsp_correlo, eps)), 'DisplayName', 'Corrélogramme')
hold on
plot(fn, 10*log10(dsp_theorique), 'r', 'DisplayName', 'DSP théorique')
hold off
xline(fn_rej, '--y', 'HandleVisibility', 'off');
xlabel('f_n'); ylabel('$\hat{S}^C_Y$', 'Interpreter', 'latex')
title(['Corrélogramme (Bartlett, K = ' num2str(K) ')'])
legend()

%% plot
figure;
subplot(4,1,1);
plot(fn,10*log10(dsp_pratique),'DisplayName', 'DSP Pratique (Périodogramme)')
hold on
plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique ')
hold off
xline(fn_rej, '--y', 'HandleVisibility', 'off'); %on trace des lignes verticales aux abscisses fn_rej pour verifier les localisations les réjections partielles
title("Dsp du signal à la sortie AR")
legend()

subplot(4,1,2);
plot(fn,10*log10(dsp_daniell),'DisplayName', 'Périodogramme de Danniell')
hold on
plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique')
hold off;
xline(fn_rej, '--y', 'HandleVisibility', 'off');
title(['Périodogramme de Daniell (M = ' num2str(M) ')'])
legend()

subplot(4,1,3);
plot(fn,10*log10(dsp_welch),'DisplayName', 'Périodogramme de Welch')
hold on
plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique ')
hold off;
xline(fn_rej, '--y', 'HandleVisibility', 'off');
title(['Périodogramme de Welch (L = ' num2str(L_welch) ', R = ' num2str(R) ')'])
legend()

subplot(4,1,4);
plot(fn_bartlett,10*log10(dsp_bartlett),'DisplayName', 'Périodogramme de Bartlett')
hold on
plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique ')
hold off;
xline(fn_rej, '--y', 'HandleVisibility', 'off');
title(['Périodogramme de Bartlett (L = ' num2str(L) ')'])

legend()