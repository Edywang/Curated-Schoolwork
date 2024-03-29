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

# Build a URL Signer.
url_signer = URLSigner(session)

# The auth.user below forces login.
@action('index', method='GET')
@action.uses('index.html', db, session, auth.user)
def index():
    rows = db(db.person.user_email == auth.current_user.get('email')).select()
    return dict(rows=rows, url_signer=url_signer)

@action('add_contact', method=['GET', 'POST'])
@action.uses('add_contact.html', auth.user, session, db)
def add_contact():
    form = Form(db.person, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        # We always want POST requests to be redirected as GETs.
        redirect(URL('index'))
    return dict(form=form, url_signer=url_signer)

@action('delete_contact/<contact_id>')
@action.uses(auth.user, session, db, url_signer.verify())
def delete_contact(contact_id=None):
    # Note that contact_id in the line above is the same contact_id in the @action
    if contact_id is not None:
        c = db(db.person.id == contact_id, db.person.user_email == auth.current_user.get('email'))
        if c is not None:
            c.delete()
    redirect(URL('index'))

@action('edit_contact/<contact_id>', method=['GET', 'POST'])
@action.uses('add_contact.html', auth.user, session, db)
def edit_contact(contact_id=None):
    # Note that contact_id in the line above is the same contact_id in the @action
    if contact_id is None:
        # Nothing to edit.  This should happen only if you tamper manually with the URL.
        redirect(URL('index'))
    # We read the contact
    c = db.person[contact_id]
    # We check if the user's email is the same as the person who made the contact
    if c is None or c.user_email != auth.current_user.get('email'):
        redirect(URL('index'))
    form = Form(db.person, record=c, deletable=False, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        # We always want POST requests to be redirected as GETs.
        redirect(URL('index'))
    return dict(form=form, url_signer=url_signer)