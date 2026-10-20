function estimation = dspdaniell(dsp,L)
% DSPDANIEL Estime la DSP par lissage du périodogramme brut.
% Entrées :
%   dsp : périodogramme brut du signal.
%   L   : longueur de la fenêtre de lissage, en échantillons fréquentiels.
% Sortie :
%   estimation : périodogramme lissé par moyenne glissante.
   
    estimation= movmean(dsp,L);

end