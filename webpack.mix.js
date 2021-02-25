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

mix
    .sass(
        './scss/global.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    )
    .sass(
        './scss/std_header.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    )
    .sass(
        './scss/std_footer.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    )
    .sass(
        './scss/contact_form.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    );

// Concatenate all CSS assets together.
mix.styles(
    [
        './css/global.css',
        './css/std_header.css',
        './css/std_footer.css',
        './css/contact_form.css'
    ],
    './css/global.css'
);

// Typescript compilation.
mix.js('./ts/global.ts', './js/global.js');