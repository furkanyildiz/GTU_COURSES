import java.util.ArrayList;
import java.util.List;

/**
 * To calculate Discrete Cosine Transform
 */
public class DiscreteCosineTransform extends DiscreateTransform1D {

    /**
     * Discrete Cosine Transform implementation
     * @param reel real numbers of equations
     * @param img imaginary numbers of equations
     * @return result of Discrete Cosine Transform
     */
    @Override
    protected List<List<Double>> transform(List<Double> reel, List<Double> img) {
        int N = reel.size();
        List<Double> OutReel = new ArrayList<>();

        for (int k = 0; k< N; ++k){


            double realSum = 0;

            for (int n=0; n< N; ++n){

                Double a = reel.get(n);


                double theta =  Math.PI / N * (n + 1/2) * k;
                realSum += a * Math.cos(theta);

            }
            OutReel.add(realSum);
        }
        List<List<Double>> Result = new ArrayList<>();
        Result.add(OutReel);
        return Result;
    }
}
