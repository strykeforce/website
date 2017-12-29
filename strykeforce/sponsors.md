---
layout: template
title: Sponsors
---

<h2 class="sponsor-category">Platinum</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "platinum" %}
  <h3>{{ d.title }}</h3>
  <img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="600px">
  {% endif %}
{% endfor %}

<h2 class="sponsor-category">Gold</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "gold" %}
  <h3>{{ d.title }}</h3>
  <img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="400px">
  {% endif %}
{% endfor %}

<h2 class="sponsor-category">Silver</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "silver" %}
  <h3>{{ d.title }}</h3>
  <img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="300px">
  {% endif %}
{% endfor %}

<h2 class="sponsor-category">Bronze</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "bronze" %}
  <h3>{{ d.title }}</h3>
  <img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="200px">
  {% endif %}
{% endfor %}
