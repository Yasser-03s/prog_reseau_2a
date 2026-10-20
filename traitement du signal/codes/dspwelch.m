function estimation = dspwelch(fn,x,L,recouvrement)
% DSPWELCH Estime la DSP par la méthode de Welch.
% Entrées :
%   fn           : vecteur des fréquences normalisées d'évaluation.
%   x            : signal dont la DSP doit être estimée.
%   L            : longueur des segments.
%   recouvrement : nombre d'échantillons communs entre deux segments successifs.
% Sortie :
%   estimation   : estimation de la DSP obtenue par moyennage des
%                  périodogrammes des segments, pondérés par une fenêtre de Hamming.

    estimation= pwelch(x,hamming(L), recouvrement,fn, 1);
end