function viewpdf( mean, sd )
%VIEWPDF Summary of this function goes here
%   Detailed explanation goes here

    x = -50 : 0.1 : 255;
    y = normpdf(x, mean, sd);

    plot((x-mean)/sd,y);

end

