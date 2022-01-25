"""
This file defines actions, i.e. functions the URLs are mapped into
The @action(path) decorator exposed the function at URL:

    http://127.0.0.1:8000/{app_name}/{path}

If app_name == '_default' then simply

    http://127.0.0.1:8000/{path}

If path == 'index' it can be omitted:

    http://127.0.0.1:8000/

The path follows the bottlepy syntax.

@action.uses('generic.html')  indicates that the action uses the generic.html template
@action.uses(session)         indicates that the action uses the session
@action.uses(db)              indicates that the action uses the db
@action.uses(T)               indicates that the action uses the i18n & pluralization
@action.uses(auth.user)       indicates that the action requires a logged in user
@action.uses(auth)            indicates that the action requires the auth object

session, db, T, auth, and tempates are examples of Fixtures.
Warning: Fixtures MUST be declared with @action.uses({fixtures}) else your app will result in undefined behavior
"""

import uuid

from py4web import action, request, abort, redirect, URL, Field
from py4web.utils.form import Form, FormStyleBulma
from py4web.utils.url_signer import URLSigner

from yatl.helpers import A
from . common import db, session, T, cache, auth, signed_url
from . models import get_user_email

url_signer = URLSigner(session)

# The auth.user below forces login.
@action('index')
@action.uses('index.html', url_signer, auth.user)
def index():
    return dict(
        # This is an example of a signed URL for the callback.
        get_posts_url = URL('get_posts', signer=url_signer),
        add_post_url = URL('add_post', signer=url_signer),
        delete_post_url = URL('delete_post', signer=url_signer),
        rate_post_url = URL('rate_post', signer=url_signer),
        # Add other callbacks here.
        user_email = get_user_email(),
        username = auth.current_user.get('first_name') + " " + auth.current_user.get("last_name")
    )

@action('get_posts')
# Note that we do not use a template.  This is a JSON API, not a "web page".
@action.uses(url_signer.verify(), auth.user)
def get_posts():
    posts = db(db.post).select().as_list()
    for post in posts:
        posters = auth.db(auth.db.auth_user.email == post.get("user_email")).select()
        #ratings = db(db.thumb.post_id == post.get("id")).select()
        myRating = db((db.thumb.post_id == post.get("id")) & (db.thumb.user_email == auth.current_user.get('email'))).select().first()
        post["username"] = posters[0].first_name + " " + posters[0].last_name
        if myRating == None:
            post["myRating"] = 0
        else:
            post["myRating"] = myRating.rating
        raters = db(db.thumb.post_id == post.get("id")).select()
        postLikers = ""
        postDislikers = ""
        totalLikes = 0
        totalDislikes = 0
        for rater in raters:
            # If the rater liked it
            if rater.rating > 0:
                if totalLikes != 0:
                    postLikers += ", "
                totalLikes += 1
                raterAuth = auth.db(auth.db.auth_user.email == rater.user_email).select().first()
                postLikers += raterAuth.first_name + " " + raterAuth.last_name
            # If the rater disliked it
            elif rater.rating < 0:
                if totalDislikes != 0:
                    postDislikers += ", "
                totalDislikes += 1
                raterAuth = auth.db(auth.db.auth_user.email == rater.user_email).select().first()
                postDislikers += raterAuth.first_name + " " + raterAuth.last_name
            # If the rater had no rating for it, we do nothing
        # If there are no ratings, our string is empty
        if postLikers == "" and postDislikers == "":
            post['ratings'] = ""
        # If there are both likes and dislikes, our string contains "Liked by " followed by likers followed by "Disliked by" followed by dislikers
        elif postLikers != "" and postDislikers != "":
            post['ratings'] = "Liked by " + postLikers + ", Disliked by " + postDislikers
        # If there are only likes, our string contains only "Liked by " followed by likers
        elif postLikers != "":
            post['ratings'] = "Liked by " + postLikers
        # Else, AKA if there are only dislikes, our string contains only "Disliked by " followed by dislikers
        else:
            post['ratings'] = "Disliked by " + postDislikers
    posts.reverse()
    return dict(posts=posts)

@action('add_post', method="POST")
# Notice that if you omit 'db' below, no changes are saved.
@action.uses(url_signer.verify(), auth.user)
def add_post():
    # NOTE: axios sends requests in json, so their content
    # is available in request.json.
    id = db.post.insert(
        user_email = get_user_email(),
        post_text = request.json.get('post'),
    )
    return dict(id=id)

@action('delete_post', method="POST")
@action.uses(url_signer.verify(), auth.user)
def delete_post():
    id = request.json.get('id')
    if id is not None:
        db(db.post.id == id).delete()
    return "ok" # Just to return something.

@action('rate_post', method="POST")
@action.uses(url_signer.verify(), auth.user)
def rate_post():
    id = request.json.get('id')
    #print("Post that should be rated is ", id, ", it is being rated by ", get_user_email(), ", and it is being rated ", request.json.get('rating'))
    if id is not None:
        myRating = db((db.thumb.post_id == id) & (db.thumb.user_email == get_user_email())).select().first()
        #print("Post updated is ", myRating)
        if myRating is None:
            newRating = db.thumb.insert(
                user_email = get_user_email(),
                post_id = id,
                rating = request.json.get('rating'),
            )
            #print("A new post has been created: ", newRating)
        else:
            myRating.update_record(
                rating = request.json.get('rating')
            )
            #print("The post has been updated to: ", myRating)
    return "ok" # Just to return something.