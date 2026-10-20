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


%% Configuration du filtre 1 (MA d'ordre 4)
A =0.95; %module des zeros
fn_rej = [-4/9 -1/4 1/4 4/9]; %fréquences normalisées des réjections
arguments = 2*pi*fn_rej; %arguments des zeros
Z = A*exp(j*arguments); %les zeros de H1

H1= poly(Z);%coeffs de la fonction de transfert qui s'annule en ces zéros
subplot(3,1,2)
zplane(H1) %on trace les zeros
title('Les Zéros de H_1')
xlabel('Partie réelle');
ylabel('Partie imaginaire');


fn= linspace(-1/2,1/2 - 1/N,N); %inclut -0.5 mais pas 0.5

%% le signal à la sortie
x=filter(H1,1,b); 

X=fftshift(fft(x));
subplot(3,1,3)
plot(t,x)
title('signal de sortie du MA (x[k])')

%% Périodogramme brut
dsp_pratique= (abs(X).^2)/N;


%% DSP théorique
h1= freqz(H1, 1, 2*pi*fn);
dsp_theorique= variance* (abs(h1).^2);

%% Périodogramme de Daniell (1 paramètre)
M=100;
dsp_daniell = dspdaniell(dsp_pratique, 100);


%% Périodogramme de Bartlett (1 paramètre)
L=300; %longueur des segments
dsp_bartlett= dspbartlett(x,L,N);
fn_bartlett= linspace(-1/2,1/2 - 1/L,L);

%% Périodogramme de Welch (2 paramètres)
L_welch=80; %longueur des segments
R=70; %recouvrement
dsp_welch = dspwelch(fn, x,L_welch, R);

%% Corrélogramme (1 paramètre)
N_retards= 20;
[Rxx, retards]= xcorr(x-mean(x), N_retards, 'biased');

figure;
plot(retards, Rxx)
xlabel('retards (m)')
ylabel('autocorr Rxx[m]')
title('corrélogramme de Rxx[m]')
legend()

%% plot
figure;
subplot(4,1,1);
plot(fn,10*log10(dsp_pratique),'DisplayName', 'DSP Pratique (Périodogramme)')
hold on
plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique ')
hold off
xline(fn_rej, '--y', 'HandleVisibility', 'off'); %on trace des lignes verticales aux abscisses fn_rej pour verifier les localisations les réjections partielles
title("Dsp du signal à la sortie MA")
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


