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

from yatl.helpers import A
from . common import db, session, T, cache, auth, signed_url
from py4web.utils.url_signer import URLSigner

# Build a URL Signer.
url_signer = URLSigner(session)

@action('index', method='GET')
@action.uses('index.html', db, session)
def view_products():
    # We get all the table rows, via a query, sorted either asc or desc depending on the param sort
    if request.params.get('sort') == 'asc':
        rows = db(db.product).select(orderby=db.product.product_cost)
    elif request.params.get('sort') == 'desc':
        rows = db(db.product).select(orderby=~db.product.product_cost)
    else:
        rows = db(db.product).select()
    return dict(rows=rows, url_signer=url_signer)

@action('add_product', method=['GET', 'POST'])
@action.uses('product_form.html', session, db)
def add_product():
    form = Form(db.product, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        # We always want POST requests to be redirected as GETs.
        redirect(URL('index'))
    return dict(form=form, url_signer=url_signer)

@action('edit_product/<product_id>', method=['GET', 'POST'])
@action.uses('product_form.html', session, db)
def edit_product(product_id=None):
    """Note that in the above declaration, the product_id argument must match
    the <product_id> argument of the @action."""
    # We read the product.
    p = db.product[product_id]
    if p is None:
        # Nothing to edit.  This should happen only if you tamper manually with the URL.
        redirect(URL('index'))
    form = Form(db.product, record=p, deletable=False, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        # We always want POST requests to be redirected as GETs.
        redirect(URL('index'))
    return dict(form=form, url_signer=url_signer)

@action('delete_product/<product_id>')
@action.uses(session, db, url_signer.verify())
def delete_product(product_id=None):
    # Note that product_id in the line above is the same product_id in the @action
    if product_id is not None:
        p = db(db.product.id == product_id)
        if p is not None:
            p.delete()
    redirect(URL('index'))

@action('toggle')
@action.uses(session, url_signer.verify())
def toggle():
    redirect(URL('index'))