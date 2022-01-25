// This will be the object that will contain the Vue attributes
// and be used to initialize it.
let app = {};

// Given an empty app object, initializes it filling its attributes,
// creates a Vue instance, and then initializes the Vue instance.
let init = (app) => {

    // This is the Vue data.
    app.data = {
        user_email: user_email,
        // Initially empty, it is then filled via the app.init method.
        posts: [], // Suggested.
        // These fields are connected to the input form via v-model.
        // When the user changes the value in the input, these fields are
        // updated as well.
        add_post_text: "",
        add_post_empty: false,
        page: "list", // Used to decide whether to show form.
        show: "-1"
    };

    // Add here the various functions you need.

    // Use this function to reindex the posts, when you get them, and when
    // you add / delete one of them.
    app.reindex = (a) => {
        // This is a convenience function that adds a _idx field
        // to each element of the array.
        let idx = 0;
        for (p of a) {
            p._idx = idx++;
            // TODO: Add here whatever other attributes should be part of a post.
        }
        return a;
    };

    app.add_post = () => {
        let error = false;
        if (app.vue.add_post_text.trim().length === 0) {
            error = true;
            app.vue.add_post_empty = true;
        }
        if (!error) {
            // We perform the actual insertion.
            app.perform_insertion();
        }
    };

    app.perform_insertion = () => {
        // We send the data to the server, from which we get the id.
        axios.post(add_post_url, {
            post: app.vue.add_post_text,
        }).then(function (response) {
            // We add the post in the input form...
            app.vue.posts.push({
                id: response.data.id,
                post: app.vue.add_post_text,
            });
            // We re-enumerate the posts.
            app.reindex(app.vue.posts);
            // ...and we blank the form.
            app.reset_form();
            app.goto('list');
        });
        axios.get(get_posts_url).then((result) => {
            app.vue.posts = app.reindex(result.data.posts);
        })
    };

    app.reset_form = () => {
        app.vue.add_post_empty = false;
        app.vue.add_post_text = "";
    };

    app.check_post = () => {
        // Not sure if we even need to check this quite frankly
        app.vue.add_post_empty  = (app.vue.add_post_text.trim().length === 0);
    };

    app.delete_post = (post_idx) => {
        // First, we figure out the post we are deleting from the _idx.
        // _idx is added by the call to app.enumerate in app.init.
        let p = app.vue.posts[post_idx];
        // Then, we call to delete that specific id.
        axios.post(delete_post_url, {id: p.id}).then(() => {
            // The deletion went through on the server. Deletes also locally.
            // Isn't it obvious that splice deletes an element?  Such is life.
            app.vue.posts.splice(post_idx, 1);
            app.reindex(app.vue.posts);
        })
    };

    app.post_over = (post_idx) => {
        app.vue.show = post_idx;
    };

    app.post_out = (post_idx) => {
        app.vue.show = -1; // -1 is used to represent none shown
    };
    
    app.set_rating = (post_idx, rating_change) => {
        // We send the data to the server.
        axios.post(rate_post_url, {
            id: post_idx,
            rating: rating_change,
        });
        axios.get(get_posts_url).then((result) => {
            app.vue.posts = app.reindex(result.data.posts);
        })
    };

    // This method handles changing our page
    app.goto = (destination) => {
        app.vue.page = destination;
    };

    // We form the dictionary of all methods, so we can assign them
    // to the Vue app in a single blow.
    app.methods = {
        add_post: app.add_post,
        check_post: app.check_post,
        delete_post: app.delete_post,
        goto: app.goto,
        post_over: app.post_over,
        post_out: app.post_out,
        set_rating: app.set_rating,
    };

    // This creates the Vue instance.
    app.vue = new Vue({
        // Which element in the webpage will be rendered, target element with ID vue-target
        el: "#vue-target",
        // app.data is defined on line 10 and is being linked here
        data: app.data,
        // app.methods is defined immediately before the app this comment is enclosed in and it is being linked here
        methods: app.methods
    });

    // And this initializes it.
    // Generally, this will be a network call to the server to load the data
    app.init = () => {
        axios.get(get_posts_url).then((result) => {
            app.vue.posts = app.reindex(result.data.posts);
        })
    };

    // Call to the initializer.
    app.init();
};

// This takes the (empty) app object, and initializes it,
// putting all the code i
init(app);
