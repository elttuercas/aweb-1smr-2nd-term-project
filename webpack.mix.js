const mix = require('laravel-mix');
const tailwindcss = require('tailwindcss')('./tailwind.config.js');

// Add TypeScript support.
mix.webpackConfig(
    {
        module: {
            rules: [
                {
                    test: /\.tsx?$/,
                    loader: 'ts-loader',
                    exclude: /node_modules/
                }
            ]
        }
    }
);

/*
 |--------------------------------------------------------------------------
 | Mix Asset Management
 |--------------------------------------------------------------------------
 |
 | Mix provides a clean, fluent API for defining some Webpack build steps
 | for your application. By default, we are compiling the CSS
 | file for the application as well as bundling up all the JS files.
 |
 */

// Concatenate all CSS assets together.
mix.styles(
    [],
    './css/global.css'
);

// Typescript compilation.
mix.js('./ts/global.ts', './js/global.js');