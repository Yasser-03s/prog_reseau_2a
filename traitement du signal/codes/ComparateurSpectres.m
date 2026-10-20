function ComparateurSpectres(x, P, Q, variance, fn_singularites, typeFiltre)
% COMPARATEURSPECTRES Compare la DSP théorique aux estimations
% spectrales du signal en sortie d'un filtre.
%
% Entrées :
%   x               : signal en sortie du filtre.
%   P               : coefficients du numérateur de la fonction
%                     de transfert du filtre.
%   Q               : coefficients du dénominateur de la fonction
%                     de transfert du filtre.
%   variance        : variance du bruit blanc en entrée du filtre.
%   fn_singularites : fréquences normalisées des zéros (MA) ou
%                     des pôles (AR), repérées sur les graphiques.
%   typeFiltre      : type de filtre étudié : 'MA' ou 'AR'.
%
% Sortie :
%   Aucune. La fonction génère cinq figures :
%   1. Périodogramme brut.
%   2. Corrélogramme pour différentes valeurs du nombre de retards.
%   3. Périodogrammes de Daniell pour différentes longueurs de fenêtre.
%   4. Périodogrammes de Bartlett pour différentes longueurs de segment.
%   5. Périodogrammes de Welch pour différents paramètres.
    
    % Vérification stricte du type de filtre
    if ~strcmpi(typeFiltre, 'MA') && ~strcmpi(typeFiltre, 'AR')
        error('Erreur : La variable typeFiltre doit être égale à ''MA'' ou ''AR''. Ce sont les deux seules valeurs possibles.');
    end
    
    N = length(x);
    fn = linspace(-1/2, 1/2 - 1/N, N);           % inclut -0.5 mais pas 0.5
    h_i= freqz(P, Q, 2*pi*fn);
    
    %% Calcul des dsp
    X = fftshift(fft(x));
    dsp_pratique = (abs(X).^2) / N;
    
    dsp_theorique = variance * (abs(h_i).^2);

    %% Périodogramme de Daniell (1 paramètre)
    M =[11, 51, 151];

    %% Périodogramme de Bartlett (1 paramètre)
    L =[500, 200 ,50]; % longueur des segments

    %% Périodogramme de Welch (2 paramètres)
    L_welch =[250,100,100]; % longueur des segments
    R =[125,50,75]; % recouvrement

    %% Corrélogramme (1 paramètre)
    N_retards =[15, 60, 250];

    %% Plot Périodogramme Brut
    figure;
    plot(fn, 10*log10(dsp_pratique), 'DisplayName', 'periodogramme brut')
    hold on
    plot(fn, 10*log10(dsp_theorique), 'r', 'DisplayName', 'DSP Théorique ')
    hold off
    xline(fn_singularites, '--y', 'HandleVisibility', 'off'); 
    title(['periodogramme brut du signal à la sortie ' typeFiltre])
    legend()
    %% Figure Corrélogramme
    figure;
    for i = 1:length(N_retards)
        K = N_retards(i);                                   % nombre de retards max (scalaire)
        
        % Estimation du corrélogramme avec une pondération de Bartlett
        % afin de limiter les effets de la troncature des retards.
        [Rxx, ~] = xcorr(x - mean(x), K, 'biased');         % retards -K..K, longueur 2K+1
        Rw = Rxx(:) .* bartlett(2*K+1);                    

        r = zeros(N,1);
        r(1:K+1)     = Rw(K+1:end);                         % retards 0..K
        r(N-K+1:N)   = Rw(1:K);                             % retards -K..-1
        dsp_correlo  = fftshift(real(fft(r)));              % réel car Rw est paire

        subplot(length(N_retards), 1, i);
        plot(fn, 10*log10(max(dsp_correlo, eps)), 'DisplayName', 'corrélogramme')
        hold on
        plot(fn, 10*log10(dsp_theorique), 'r', 'DisplayName', 'DSP Théorique ')
        hold off
        xline(fn_singularites, '--y', 'HandleVisibility', 'off');
        title(['corrélogramme pour ' num2str(K) ' retards (fenêtre de Bartlett)'])
        legend()
    end


    %% Plot Daniell
    figure;
    for i = 1:length(M)

        dsp_daniell = dspdaniell(dsp_pratique, M(i));

        subplot(length(M), 1, i);
        plot(fn, 10*log10(dsp_daniell), 'DisplayName', 'Périodogramme de Danniell')
        hold on
        plot(fn, 10*log10(dsp_theorique), 'r', 'DisplayName', 'DSP Théorique')
        hold off;
        xline(fn_singularites, '--y', 'HandleVisibility', 'off');
        title(['Périodogramme de Daniell (M = ' num2str(M(i)) ')'])
        legend()
    end

    %% Plot Bartlett
    figure;
    for i = 1:length(L)
        fprintf('Essai Bartlet pour L = %d\n', L(i));
        dsp_bartlett= dspbartlett(x,L(i),N);
        fn_bartlett= linspace(-1/2,1/2 - 1/L(i),L(i));
        subplot(length(L),1,i);
        plot(fn_bartlett,10*log10(dsp_bartlett),'DisplayName', 'Périodogramme de Bartlett')
        hold on
        plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique ')
        hold off;
        xline(fn_singularites, '--y', 'HandleVisibility', 'off');
        title(['Périodogramme de Bartlett (L = ' num2str(L(i)) ')'])
        legend()
    end

    %% Plot Welch
    figure;
    for i = 1:length(L_welch)
        dsp_welch = dspwelch(fn, x, L_welch(i), R(i));
        subplot(length(L_welch),1,i);
        plot(fn,10*log10(dsp_welch),'DisplayName', 'Périodogramme de Welch')
        hold on
        plot(fn,10*log10(dsp_theorique), 'r','DisplayName', 'DSP Théorique ')
        hold off;
        xline(fn_singularites, '--y', 'HandleVisibility', 'off');
        title(['Périodogramme de Welch (L = ' num2str(L_welch(i)) ', R = ' num2str(R(i)) ')'])
        legend()
    end
end
