function estimation = dspbartlett(x,L,N)
% DSPBARTLETT Estime la DSP par la méthode de Bartlett.
% Entrées :
%   x : signal à analyser.
%   L : longueur des segments, sans recouvrement.
%   N : nombre total d'échantillons du signal.
% Sortie :
%   estimation : moyenne des périodogrammes des segments, présentée avec les fréquences centrées par fftshift.
    n= floor(N/L); %on découpe le signal en n segments de taille L
    estimation= zeros(1,L);
    for k = 1:n
        indices = (k-1)*L + (1:L); % Indices des points du segment actuel
        segment = x(indices);

        % 1. Calcul de la FFT sur la taille du segment 
        X_segment = fft(segment); 

        % 2. Périodogramme du segment : |X|^2 / L 
        % et accumulation dans le vecteur global
        estimation = estimation + (abs(X_segment).^2) / L;
    end

    % 3. Calcul de la moyenne sur les n segments puis décalage des fréquences
    estimation = fftshift(estimation / n);
end