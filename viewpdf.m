function viewpdf( mean, sd )
%VIEWPDF Summary of this function goes here
%   Detailed explanation goes here

    x = -300 : 0.1 : 300;
    y = normpdf(x, mean, sd);

    plot(x,y);

end

