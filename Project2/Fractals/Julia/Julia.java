import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;

public class Julia extends JPanel {
    // Global constants
    private final int juliaSizeWidth = 800;
    private final int juliaSizeHeight = 600; 
    private final int numberIterations = 40; // 25 || 35 || 50 || 100 || 250 - Change this value

    // In Julia the value for Zc should be a constant
    private final double zcReal = -0.8; // - Change this value
    private final double zcImaginary = 0.22015; // - Change this value

    // Values to calculate the real and imaginary part of z
    private final double zoom = 1.0;
    private final double moveX = 0.0;
    private final double moveY = 0.0;

    // Constructor
    public Julia() {
        // Configuration for the size of the JPanel
        setPreferredSize(new Dimension(juliaSizeWidth, juliaSizeHeight));
        setBackground(Color.white);
    }

    public void drawJulia(Graphics2D graphic2D) {
        // Configuration of the image to store the julia fractal
        BufferedImage juliaImage = new BufferedImage(
            juliaSizeWidth, 
            juliaSizeHeight, 
            BufferedImage.TYPE_INT_RGB
        );

        double zReal = 0.0;
        double zImaginary = 0.0;
    
        for(int x = 0; x < juliaSizeWidth; x++) {
            for(int y = 0; y < juliaSizeHeight; y++) {

                // Calculate the real part of Z
                zReal = 1.5 * (x - juliaSizeWidth / 2) / (0.5 * zoom * juliaSizeWidth) + moveX;
                // Calculate the imaginary part of Z
                zImaginary = (y - juliaSizeHeight / 2) / (0.5 * zoom * juliaSizeHeight) + moveY; 

                // Do iteration process if:
                // 1. The number of iterations is greater than 0
                // 2. The point is inside the circle with radius 2
                float iteration = numberIterations;
                while(iteration > 0 && Math.pow(zReal, 2) + Math.pow(zImaginary, 2) < 4) {
                    double zRealAux = Math.pow(zReal, 2) - Math.pow(zImaginary, 2) + zcReal;
                    zImaginary = 2.0 * zReal * zImaginary + zcImaginary;
                    zReal = zRealAux;
                    iteration -= 1;
                }

                // Get the color for the pixel
                float hueValue = (numberIterations / iteration) % 1;
                float saturationValue = 1;
                float brightnessValue = iteration < numberIterations ? 1 : 0;

                int colorPixel = Color.HSBtoRGB(hueValue, saturationValue, brightnessValue);
                juliaImage.setRGB(x, y, colorPixel);
            }
        }
        graphic2D.drawImage(juliaImage, 0, 0, null);
    }

    @Override
    public void paintComponent(Graphics graphic) {
        super.paintComponent(graphic);
        Graphics2D graphic2D = (Graphics2D) graphic;
        graphic2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        drawJulia(graphic2D);
    }

    public static void main(String[] args){
        SwingUtilities.invokeLater(() -> {
            // Configure the frame for Julia
            JFrame juliaFrame = new JFrame();
            
            juliaFrame.setTitle("Julia");

            juliaFrame.add(new Julia(), BorderLayout.CENTER);

            juliaFrame.setLocationRelativeTo(null);
            juliaFrame.setVisible(true);

            juliaFrame.pack();
            juliaFrame.setResizable(false);
            juliaFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        });
    }
}
